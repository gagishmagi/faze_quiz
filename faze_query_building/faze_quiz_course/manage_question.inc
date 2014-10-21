<?php 
function faze_quiz_course_manage_questions() {
  if (isset($_POST['action'])){
    if($_POST['action']=="add_quesion_to_corse" && isset($_POST['qid']) && isset($_POST['sid']))
    {
      $qid=$_POST['qid'];
      $sid=$_POST['sid'];
      if (faze_quiz_course_add_question_to_subject($qid, $sid)!=1){
        header("HTTP/1.0 404 Not Found");
        return "";
      }
      $subject=faze_quiz_course_get_subject($sid);
      $returnData->course_name=$subject->course_name;
      $returnData->subject_name=$subject->name;
      $returnData->sid=$sid;
      $returnData->qid=$qid;
      $returnData->cid=$subject->cid;
      echo json_encode($returnData);
    }
    //else if ($_POST['action']=="...")
  }
  else
  {
    
    faze_jquery_ui_drag_drop();
    faze_jquery_sticky();
    faze_jquery_multiselect_widget();
    drupal_add_js(drupal_get_path('module', 'faze_quiz_course') . '/js/faze_quiz_course_manage_questions.js');
    drupal_add_css(drupal_get_path('module', 'faze_quiz_course') . '/theme/faze_quiz_course_manage_questions.css');
    
    require_once drupal_get_path('module', 'faze_quiz_course').'/question_table.inc';
  
    return  faze_quiz_course_get_question_table(
        $filter_require=array(nid,question,subject,user),
        $selectors=array('sid'=>$_GET["sid"])
      );
  }
}

