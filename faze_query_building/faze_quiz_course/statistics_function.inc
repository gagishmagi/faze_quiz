<?php

function faze_quiz_course_get_student_statistics_in_course($cid,$student_uid){
  $sql = "SELECT 
			COUNT( field_task_nid_value ) AS count, 
			AVG( field_grade_value ) AS avrgGrade
		  FROM `content_type_quiz`

          LEFT JOIN `content_type_task` ON `content_type_quiz`.`field_task_nid_value` = `content_type_task`.`nid`
          LEFT JOIN `node` ON `node`.`nid` = `content_type_quiz`.`nid`

		  WHERE `field_completed_value` =1
			AND `content_type_task`.`field_course_cid_value` = %d
			AND `node`.`uid` = %d 
	      GROUP BY `field_course_cid_value`";
  $result = db_query($sql, $cid,$student_uid);
  $statistics->countQuiz=0;
  $statistics->avrgGrade=0;
  if (($reference = db_fetch_object($result)) != NULL){
    $statistics->countQuiz=$reference->count;
    $statistics->avrgGrade=$reference->avrgGrade;
  }
  return $statistics;
}

function faze_quiz_course_get_task_statistics($task)
{
  $sql = "SELECT 	
  				COUNT( field_task_nid_value ) AS count, 
  				AVG( field_grade_value ) AS avrgGrade
			FROM `content_type_quiz`
			WHERE `field_completed_value` =1
				AND `field_task_nid_value` =%d
			GROUP BY `field_task_nid_value`";
  $result = db_query($sql, $task->nid);
  $statistics->countQuiz=0;
  $statistics->avrgGrade=0;
 
  if (($reference = db_fetch_object($result)) != NULL){
    $statistics->countQuiz=$reference->count;
    $statistics->avrgGrade=$reference->avrgGrade;
  }
  
  /*$sql = "SELECT 
  			 COUNT( `field_grade_value` ) AS count, 
  			 `field_grade_value` AS grade
		   FROM `content_type_quiz`
		   WHERE `field_completed_value` =1
			AND `field_task_nid_value` = %d
           GROUP BY `field_grade_value`";
  $result = db_query($sql, $task->nid);
  */
  
  $sql= "select
  			concat(10 * round(field_grade_value*10), '-', 10 * round(field_grade_value*10) + 9) as `range`,
  			count(*) as `count`
		from content_type_quiz
		WHERE `field_completed_value` =1
		  AND `field_task_nid_value` = %d
		group by 1
		order by field_grade_value;";
  $result = db_query($sql, $task->nid);
   
  $statistics->distribution=array();
  while (($reference = db_fetch_object($result)) != NULL)
  {
    $statistics->distribution[]=$reference;
  }
  return $statistics;
}

function faze_quiz_course_get_count_question_in_task($task){
  $FixedQuestionJson=json_decode($task->field_fixedquestion_json[0]['value']);
  $randomQuestion=json_decode($task->field_randomquestion_json[0]['value']);
  
  $count=count($FixedQuestionJson);

  foreach ($randomQuestion as $value)
    $count+=$value->count;
  
  return $count;
}