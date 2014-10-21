<?php

function faze_quiz_course_course_page($cid){
  require_once drupal_get_path('module', 'faze_quiz_course').'/statistics_function.inc';
  $course=faze_quiz_course_get_course($cid);

  drupal_set_title(t('מקצוע: ').$course->name);

  $studentArray=faze_quiz_course_get_student_in_course($cid);
  foreach ($studentArray AS $student){
   $student->statistics=faze_quiz_course_get_student_statistics_in_course($cid,$student->uid);
  }
  
  $taskArray=faze_quiz_course_get_task_in_course($cid);
  foreach ($taskArray AS $task){
   $task->statistics=faze_quiz_course_get_task_statistics($task);
  }
  
  return theme('faze_quiz_course_course_page',$course,$studentArray,$taskArray);

}
