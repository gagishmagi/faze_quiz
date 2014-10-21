<?php

function faze_quiz_course_task_page($node){
  require_once drupal_get_path('module', 'faze_quiz_course').'/question_table.inc';
  //get all student of course.
  //get the task ditalis.
  //acsess the quiz to the techer.
  drupal_set_title(t('משימה: ').$node->title);

  $FixedQuestionNidArray= array();
  $FixedQuestionJson=json_decode($node->field_fixedquestion_json[0]['value']);
  foreach ($FixedQuestionJson as $value){
    $FixedQuestionNidArray[]=$value->q_nid;
  }
  
  if (count($FixedQuestionNidArray)!=0){
    $FixedQuestionTable = faze_quiz_course_get_question_table(
      $filter_require=array(),
      $selectors=array('nids'=>implode(",", $FixedQuestionNidArray)),
      $table_col=array('nid','question'),
      $question_per_page=99999
    );
  }
  else
    $FixedQuestionTable=t('אין שאלות קבועות');
  
  

  $randomQuestion=json_decode($node->field_randomquestion_json[0]['value']);
  foreach ($randomQuestion as $value){
    $value->name=faze_quiz_course_get_subject_name($value->sid);
  }
  
  $studentArray=faze_quiz_course_get_student_in_course($node->field_course_cid[0]['value']);
  foreach ($studentArray AS $student){
    $quiz=faze_quiz_course_get_quiz_by_task_student($node->nid, $student->uid);
    if ($quiz==null){
      $student->q_nid=null;
      $student->completed=null;
    }
    else
    {
      $student->q_nid=$quiz->q_nid;
      $student->completed=$quiz->completed;
    }
  }
  
  return theme('faze_quiz_course_task_page',$node,$FixedQuestionTable,$randomQuestion,$studentArray);
}

/////------------------------------------
//qdd quiz by task
/////------------------------------------

function faze_quiz_course_add_quiz_by_task_page($task_node){
  // nead to chack if there is not quiz for this task to the user.
  global $user;
  $nid=faze_quiz_course_get_quiz_by_task_student($task_node->nid, $user->uid)->q_nid;
  //if (intval($nid)==0)
    $nid=faze_quiz_course_add_quiz_by_task($task_node,$user);
  //else
  //  drupal_set_message(t('כבר יצרת מבחן עבור משימה זו.'));
  
  drupal_goto("quiz/".$nid);
}

function faze_quiz_course_add_quiz_by_task($task_node, $user = null){
  $node->title = taxonomy_get_term($tid)->name;
  $select_questions=array();
  $questions=array();
  //----------FixedQuestion
  $FixedQuestionNidArray= array();
  $FixedQuestionJson=json_decode($task_node->field_fixedquestion_json[0]['value']);
  foreach ($FixedQuestionJson as $value){
    $select_questions[]=$value->q_nid;
    $questions[]=node_load($value->q_nid);
  }
  //----------randomQuestion
  $user_leval=faze_quiz_course_get_user_level_in_course($user,$task_node->field_cid);
  $randomQuestion=json_decode($task_node->field_randomquestion_json[0]['value']);
  foreach ($randomQuestion as $value){
    for ($i = 1; $i <= $value->count; $i++) {
      $question=faze_quiz_course_get_rund_question($value->sid,$user_leval,$select_questions);
      if (!$question) // there is no more question for this taxonomy
      {
        drupal_set_message(t("שים לב, במערכת אין מספיק שאלות עבור מבחן זה"));
        break;
      }
      $select_questions[]=$question->nid;
      $questions[]=$question;
    }
  }
  
  if (count($questions)==0){
    return null;
  }
  $quiz_node=node_load(faze_quiz_build_quiz($questions, $user));
  $quiz_node->field_task_nid[0]['value']=$task_node->nid;
  node_save($quiz_node);
  //dsm($quiz_node);
  return $quiz_node->nid;
}

function faze_quiz_course_get_rund_question($sid,$user_leval,$exclud_qid=array()){
  array_push($exclud_qid,0);
  module_load_include('inc', 'faze_quiz', 'normal_dist');
  $s=variable_get('faze_quiz_gauss_s', 0.2);
  $difficulty=faze_quiz_gauss_ms($user_leval,$s);
  $result = db_query("
    SELECT node.nid AS nid,
    node_data_field_difficulty.field_difficulty_value AS difficulty
    FROM node node 
    INNER JOIN faze_quiz_course_question_subject ON node.nid = faze_quiz_course_question_subject.qid
    LEFT JOIN content_field_difficulty node_data_field_difficulty ON node.vid = node_data_field_difficulty.vid
    WHERE (faze_quiz_course_question_subject.sid = %d) AND (node.type in ('question')) AND (node.status = 0)
    AND node.nid NOT IN (".db_placeholders($exclud_qid, 'int').")
    ORDER BY ABS(node_data_field_difficulty.field_difficulty_value-%f), RAND() ASC
    LIMIT 1" 
    , array_merge(array($sid) , $exclud_qid , array($difficulty)));
  $row = db_fetch_object($result);
  return node_load($row->nid);
}
