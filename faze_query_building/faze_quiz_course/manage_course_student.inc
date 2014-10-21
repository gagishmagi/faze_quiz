<?php 
function faze_quiz_course_manage_course_student() {
  
  if (isset($_POST['action'])){
    /*if($_POST['action']=="add_student" && isset($_POST['cid']) && isset($_POST['uid']))
    {
      $cid=$_POST['cid'];
      $uid=$_POST['uid'];
      //print faze_quiz_course_add_student_to_course($cid, $uid);
      if (faze_quiz_course_add_student_to_course($cid, $uid)!=1){
        header("HTTP/1.0 404 Not Found"); 
        return "";
      }
      $course=faze_quiz_course_get_course($cid);
      $returnData->course_name=$course->name;
      $returnData->uid=$uid;
      $returnData->cid=$cid;
      echo json_encode($returnData);
    }
    */
    if($_POST['action']=="add_student" && isset($_POST['data']))
    {
      $cid=$_POST['data']['cid'];
      $uid_array=$_POST['data']['uid'];
      foreach ($uid_array as $key => $uid) 
        if (faze_quiz_course_add_student_to_course($cid, $uid)!=1)
          unset($uid_array[$key]);
      $course=faze_quiz_course_get_course($cid);
      $returnData->course_name=$course->name;
      $returnData->uid=$uid_array;
      $returnData->cid=$cid;
      echo json_encode($returnData);
    }
    //else if ($_POST['action']=="...")
  }
  else
    {
    
    $filter = array(
      "name" => array(
        'table' => 'users',
        'column' => 'name',
      ),
    );
    
    $filter_obj = faze_query_building_filter($filter);
    
    $headers = array(
      array('data' => ''),
      array('data' => '#', 'field' => 'uid', 'sort'=> 'asc'),
      array('data' => 'שם', 'field' => 'name'),
      array('data' => 'מקצועות'),
    );
  
    $sql = "SELECT `users`.`uid` as uid";
    $sql .= " FROM `users`";
    $sql .= " LEFT JOIN `users_roles` ON `users`.`uid`=`users_roles`.`uid`";
    if (isset($_GET["cid"])){
      $sql .= " LEFT JOIN `faze_quiz_course_course_student` ON `users`.`uid`=`faze_quiz_course_course_student`.`uid`";
    }
    $sql .= " WHERE `users_roles`.`rid`=4";
    if (isset($_GET["cid"])){
      $sql .= " AND `faze_quiz_course_course_student`.`cid` = ".((int)$_GET["cid"]);
    }

    $sql .= " AND ".$filter_obj['sql'];
    $sql .= tablesort_sql($headers);
    $limit = 50;
  
    $result = pager_query($sql, $limit, 0, NULL);
    
    $users=null;
    if($result){
      $users=array();
      while($row = db_fetch_array($result)) {
        $users[]=user_load($row['uid']);
      }
    }
     
    return(theme('faze_quiz_course_manage_course_student', $users, $filter_obj['table'],$headers,$limit));
  }
}
