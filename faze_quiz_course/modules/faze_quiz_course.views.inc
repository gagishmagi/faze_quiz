<?php

/**
 * Implemrntaion of hook_views_data().
 *
 */
function faze_quiz_course_views_data() {
  $data['faze_quiz_course_course']['table']['group'] = t('קורסים');
  
  $data['faze_quiz_course_course']['table']['base'] = array(
    'field' => 'cid', 
    'title' => t('טבלת קורסים'), 
    'help' => t("טבלה השומרת את רשימת הקורסים ומקשרת אותם למורה."), 
    'weight' => -10,
  );
  
  $data['faze_quiz_course_course']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid', 
      'field' => 'teacher_uid',
    ),
    'faze_quiz_course_course_subject' => array(
      'left_field' => 'cid', 
      'field' => 'cid',
    ),
  );
  
  $data['users']['table']['join'] = array(
    'faze_quiz_course_course' => array(
      'left_field' => 'teacher_uid', 
      'field' => 'uid',
    ),
  );
    
  
  $data['faze_quiz_course_course']['teacher_uid'] = array(
    'title' => t('מורה'),
    'help' => t('uid של המורה'),
    'relationship' => array(
      'base' => 'users', 
      'field' => 'uid', 
      'handler' => 'views_handler_relationship', 
      'label' => t('מורה'),
    ),
  );
  
  $data['faze_quiz_course_course']['cid'] = array(
    'title' => t('מספר קורס'),
    'help' => t('cid'), 
    'field' => array(
      'handler' => 'views_handler_field_numeric', 
      'click sortable' => TRUE,
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  $data['faze_quiz_course_course']['name'] = array(
    'title' => t('שם קורס'),
    'help' => t('שם הקורס'),
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  //---------------------------------------------------------------------
  $data['faze_quiz_course_course_subject']['table']['group'] = t('קורסים');
  
  $data['faze_quiz_course_course_subject']['table']['base'] = array(
    'field' => 'cid', 
    'title' => t('טבלת נושאים בקורס'), 
    'help' => t("טבלה השומרת את הנושאים בקורסים."), 
    'weight' => -10,
  );
  
  $data['faze_quiz_course_course_subject']['table']['join'] = array(
    'faze_quiz_course_course' => array(
      'left_field' => 'cid', 
      'field' => 'cid',
    ),
    'faze_quiz_course_question_subject' => array(
      'left_field' => 'sid', 
      'field' => 'sid',
    ),
  );
  
  $data['faze_quiz_course_course_subject']['cid'] = array(
    'title' => t('קורס'),
  	'help' => t('id של הקורס'),
    'relationship' => array(
      'base' => 'faze_quiz_course_course', 
      'field' => 'cid', 
      'handler' => 'views_handler_relationship', 
      'label' => t('קורס'),
    ),
  );
  
  $data['faze_quiz_course_course_subject']['sid'] = array(
    'title' => t('מספר נושא'), 
    'help' => t('id של הנושא'),
    'field' => array(
      'handler' => 'views_handler_field_numeric', 
      'click sortable' => TRUE,
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  $data['faze_quiz_course_course_subject']['name'] = array(
    'title' => t('שם הנושא'), 
    'help' => t('שם הנושא'),
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  
  //---------------------------------------------------------------------
  $data['faze_quiz_course_question_subject']['table']['group'] = t('קורסים');
    
  $data['faze_quiz_course_question_subject']['table']['base'] = array(
    'field' => 'sid', 
    'title' => t('קשר- נושאים בקורס שאלות'), 
    'help' => t("טבלה המקשרת בין נושאים בקרוס לשאלות."), 
    'weight' => -10,
  );
  
  $data['faze_quiz_course_question_subject']['table']['join'] = array(
    'faze_quiz_course_course_subject' => array(
      'left_field' => 'sid', 
      'field' => 'sid',
    ),
    'node' => array(
      'left_field' => 'nid', 
      'field' => 'qid',
    ),
  );
  
  $data['node']['table']['join'] = array(
    'faze_quiz_course_question_subject' => array(
      'left_field' => 'qid', 
      'field' => 'nid',
    ),
  );
  
  
  $data['faze_quiz_course_question_subject']['sid'] = array(
    'title' => t('נושא קורס'),
  	'help' => t('id של נושא בקורס'),
    'relationship' => array(
      'base' => 'faze_quiz_course_course_subject', 
      'base field' => 'sid',
      'field' => 'sid',
      'handler' => 'views_handler_relationship', 
      'label' => t('נושא בקורס'),
    ),
  );

  $data['faze_quiz_course_question_subject']['qid'] = array(
    'title' => t('שאלה'),
  	'help' => t('nid של שאלה'),
    'relationship' => array(
      'base' => 'node',  
      'field' => 'nid',
      'handler' => 'views_handler_relationship', 
      'label' => t('שאלה'),
    ),
  );
  

  
  
  return $data;
}