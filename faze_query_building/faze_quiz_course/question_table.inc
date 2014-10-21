<?php 
//dynamic question table

function faze_quiz_course_get_question_table(
    $filter_require=array(nid,question,subject,user),
    $selectors=array('sid'=>null,'cid'=>null,'nids'=>null), //nids- comma_separated q_nid
    $table_col=array('nid','question','subject','difficulty','u_name'),
    $question_per_page=50
  )
{
  $filter = array();
  if (in_array("nid", $filter_require)){
    $filter["nid"] = array(
      'table' => 'node',
      'column' => 'nid',
      'type' => 'numeric',
    );
  }
  if (in_array("question", $filter_require)){
    $filter["question"] = array(
      'table' => 'content_type_question',
      'column' => 'field_question_value',
    );
  }
  if (in_array("subject", $filter_require)){
    $filter["subject"] = array(
      'table' => 'faze_quiz_course_course',
      'column' => 'cid',
      'name' => "מקצוע",
      'default' => '',
      'type' => 'numeric',
      'options' => array(),
    );
    /*
    $filter["subject"]['options']['']= "-בחר-";
    $filter["subject"]['options']+=faze_quiz_get_question_subject_array_with_depth();
    */
    /*$filter["subject"]['options']=faze_quiz_get_question_subject_multi_array();*/
    $sql="SELECT DISTINCT teacher_uid AS uid,
      name AS course_name,
      cid AS cid
      FROM faze_quiz_course_course 
   		INNER JOIN users_roles users_roles_value_0 ON teacher_uid = users_roles_value_0.uid AND users_roles_value_0.rid = 3
   		WHERE (users_roles_value_0.rid = 3)";
    $result = db_query($sql);
    while ($row= db_fetch_object($result)) {
      $filter["subject"]['options'][$row->cid] = $row->course_name;
    }
  }
  if (in_array("user", $filter_require)){
    $filter["user"] = array(
      'table' => 'users',
      'column' => 'uid',
      'name' => "מורה",
      'default' => '',
      'type' => 'numeric',
      'options' => array(),
    );
    //$filter["user"]['options'][''] = "-בחר-";
    $sql="SELECT users.uid AS uid,
     	  	users.name AS user_name
   		FROM users  
   		INNER JOIN users_roles users_roles_value_0 ON users.uid = users_roles_value_0.uid AND users_roles_value_0.rid = 3
   		WHERE (users_roles_value_0.rid = 3) AND (users.status <> 0)";
    $result = db_query($sql);
    while ($row= db_fetch_object($result)) {
      $filter["user"]['options'][$row->uid] = $row->user_name;
    }
  }
  
  $filter_obj = faze_query_building_filter($filter);
  
  $headers = array();
  if (in_array("nid", $table_col))
    $headers[]=array('data' => '#', 'field' => 'nid', 'sort'=> 'desc');
  if (in_array("question", $table_col))  
    $headers[]=array('data' => 'שאלה', 'field' => 'question');
  if (in_array("subject", $table_col))
    $headers[]=array('data' => 'מקצוע', 'field' => 'subject');
  if (in_array("difficulty", $table_col))
    $headers[]=array('data' => 'רמת קושי', 'field' => 'difficulty');
  if (in_array("u_name", $table_col))
    $headers[]=array('data' => 'מורה', 'field' => 'u_name');


  $sql = "SELECT 
  			DISTINCT `node`.`nid` as nid,
  			`content_type_question`.`field_question_value` as question,
  			`content_field_difficulty`.`field_difficulty_value` as difficulty,
        `term_node`.`tid` as tid,
        `faze_quiz_course_course`.`cid` as cid,
  			`users`.`name` as u_name
  			";
  $sql .= " FROM `node`";
  $sql .= " JOIN `users` ON `node`.`uid`=`users`.`uid`";
  $sql .= " JOIN `term_node` ON `node`.`nid`=`term_node`.`nid`";
  $sql .= " JOIN `content_type_question` ON `node`.`nid`=`content_type_question`.`nid`";
  $sql .= " JOIN `content_field_difficulty` ON `node`.`nid`=`content_field_difficulty`.`nid`";
  $sql .= " LEFT JOIN `faze_quiz_course_question_subject` ON `node`.`nid`=`faze_quiz_course_question_subject`.`qid`";
  $sql .= " LEFT JOIN `faze_quiz_course_course_subject` ON `faze_quiz_course_question_subject`.`sid`=`faze_quiz_course_course_subject`.`sid`";
  $sql .= " LEFT JOIN `faze_quiz_course_course` ON `faze_quiz_course_course`.`cid`=`faze_quiz_course_course_subject`.`cid`";
  $sql .= " WHERE `node`.`type`='question'";
  if (isset($selectors['sid']) && $selectors['sid']!=null)
    $sql .= " AND `faze_quiz_course_question_subject`.`sid` = ".((int)$selectors['sid']);
  if (isset($selectors['cid']) && $selectors['cid']!=null)
    $sql .= " AND `faze_quiz_course_course`.`cid` = ".((int)$selectors['cid']);
  if (isset($selectors['nids']) && $selectors['nids']!=null)
    $sql .= " AND `node`.`nid` IN (".($selectors['nids']).")";
  if (count($filter_require)>0)
    $sql .= " AND ".$filter_obj['sql'];
  $sql .= tablesort_sql($headers);
  $limit = $question_per_page;

  $result = pager_query($sql, $limit, 0, NULL);
  
  $question_nodes=null;
  if($result){
    $question_nodes=array();
    while($row = db_fetch_array($result)) {
      $question_nodes[]=node_load($row['nid']);
    }
  }
  
  return(theme('faze_quiz_course_question_table', $question_nodes, $filter_obj['table'],$headers,$limit,$table_col));
  
}
