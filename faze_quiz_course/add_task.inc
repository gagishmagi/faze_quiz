<?php
function faze_quiz_course_add_task($nid){
  if (isset($_POST['action'])){
    if($_POST['action']=="get_question_table")
    {
        require_once drupal_get_path('module', 'faze_quiz_course').'/question_table.inc';
        if (!isset($_POST['FixedQuestionJson'])){
          print faze_quiz_course_get_question_table(
            $filter_require=array(nid,question),
            $selectors=array('cid'=>$_GET["cid"],'sid'=>$_GET["sid"]),
            $table_col=array('nid','question'),
            $question_per_page=5
          );
        }
        else{ //isset($_POST['FixedQuestionJson'])
          $FixedQuestionNidArray= array();
          $FixedQuestionJson=json_decode($_POST['FixedQuestionJson']);
          foreach ($FixedQuestionJson as $value){
            $FixedQuestionNidArray[]=$value->q_nid;
          }
          
          print faze_quiz_course_get_question_table(
            $filter_require=array(),
            $selectors=array('nids'=>implode(",", $FixedQuestionNidArray)),
            $table_col=array('nid','question'),
            $question_per_page=99999
          );
        }
    }
    if($_POST['action']=="get_corse_subject_json")
    {
      print json_encode(faze_quiz_course_get_course($_GET["cid"]));
    }
  }
  else {
    //drupal_add_css(drupal_get_path('module', 'faze_quiz_course') . '/fancybox/jquery.fancybox.css');
    drupal_add_css(drupal_get_path('module', 'faze_quiz_course') . '/theme/faze_quiz_course_question_table.css');
    drupal_add_css(drupal_get_path('module', 'faze_quiz_course') . '/theme/faze_quiz_course_add_task.css');
    faze_jquery_ui_dialog();
    //drupal_add_js(drupal_get_path('module', 'faze_quiz_course') . '/fancybox/jquery.fancybox.js?v=2.1.3');
    drupal_add_js(drupal_get_path('module', 'faze_quiz_course') . '/js/faze_quiz_course_question_table.js');
    drupal_add_js(drupal_get_path('module', 'faze_quiz_course') . '/js/faze_quiz_course_add_task.js');

    return drupal_get_form('faze_quiz_course_addtask_form');
  }
}


function faze_quiz_course_addtask_form(){
  $node=null;
  if (arg(0)=='edit_task')
    $node=node_load(arg(1));
  
  global $user;
  $form = array();
    
  $form['faze_quiz_course_addtask_course'] = array(
    '#type' => 'select',
	'#title' => t('מקצוע'),
	'#description' => t('המקצוע אליו המשימה מתייחסת.'),
	'#default_value' => $node?$node->field_course_cid[0]['value']:$_GET["cid"],
	'#required' => TRUE,
    '#options' => array(),
  );

  $courses=faze_quiz_course_get_techer_courses($user->uid);
  foreach ($courses as $value)
    $form['faze_quiz_course_addtask_course']['#options'][$value->cid]=$value->name;
    
  $form['faze_quiz_course_addtask_task_title'] = array(
    '#type' => 'textfield',
	'#title' => t('כותרת משימה'),
	'#default_value' => $node?$node->title:"",
	'#required' => TRUE,
  );
  
  $form['faze_quiz_course_addtask_task_description'] = array(
    '#type' => 'textarea',
	'#title' => t('הסבר משימה'),
	'#description' => t('טקסט חופשי המסביר את המשימה.'),
	'#default_value' => $node?$node->body:"",
	'#required' => FALSE,
  );
  
  $form['faze_quiz_course_addtask_FixedQuestion_fieldset'] = array(
    '#type' => 'fieldset',
	'#title' => t('שאלות קבועות (0)'),
	'#description' => t('רשימה של שאלות שיופיעו במבחן'),
    '#attributes' => array('class' => 'FixedQuestion_fieldset'),
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE,  
  );    
    
  $form['faze_quiz_course_addtask_FixedQuestion_fieldset']
        ['faze_quiz_course_addtask_FixedQuestion_nid'] = array(
    '#type' => 'hidden',
    '#default_value' => $node?$node->field_fixedquestion_json[0]['value']:"",
    //json array of question nid, will handle by js.
  );
    
  $form['faze_quiz_course_addtask_randomQuestion_fieldset'] = array(
    '#type' => 'fieldset',
	'#title' => t('שאלות אקראיות (0)'),
  	'#description' => t('כמות שאלות מכל נושא שיופיעו במבחן. השאלות יוגרלו עבור כל תלמיד בהתאם לרמת הידע שלו בחומר.'),
    '#attributes' => array('class' => 'randomQuestion_fieldset'),
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE,
  );    
    
  $form['faze_quiz_course_addtask_randomQuestion_fieldset']
        ['faze_quiz_course_addtask_randomQuestion_sid'] = array(
    '#type' => 'hidden',
    '#default_value' => $node?$node->field_randomquestion_json[0]['value']:"",
    //hson array of sid count object, will handle by js.
  );

  
  $form['submit'] = array(
    '#type' => 'submit',
	'#value' => t('הוסף משימה'),
  );
  
  return $form;
}

function faze_quiz_course_addtask_form_submit(&$form, &$form_state){
  global $user;
  //dsm(json_decode($form_state['values']['faze_quiz_course_addtask_FixedQuestion_nid']));
  //dsm(json_decode($form_state['values']['faze_quiz_course_addtask_randomQuestion_sid']));
  //dsm($form_state['values']);
  
  $node=null;
  if (arg(0)=='edit_task'){
    $node=node_load(arg(1));
    if(!faze_quiz_course_access_edit_task($node))
      return;
  }
  else
  {
    $node = new StdClass();
    $node->uid=$user->uid;
    $node->type = 'task';  
    $node->status = 0;  
  }
  

  $node->title = $form_state['values']['faze_quiz_course_addtask_task_title'];  
  $node->body = $form_state['values']['faze_quiz_course_addtask_task_description'];
  $node->field_course_cid[0]['value']=$form_state['values']['faze_quiz_course_addtask_course'];
  $node->field_fixedquestion_json[0]['value']=$form_state['values']['faze_quiz_course_addtask_FixedQuestion_nid'];
  $node->field_randomquestion_json[0]['value']=$form_state['values']['faze_quiz_course_addtask_randomQuestion_sid'];
    
  node_save($node);
  drupal_goto("task/".$node->nid);
}



