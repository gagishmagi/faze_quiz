<?php
// $Id$
  faze_jquery_ui_drag_drop();
  faze_jquery_sticky();
  drupal_add_js(drupal_get_path('module', 'faze_quiz_course') . '/js/faze_quiz_course_manage_course_student.js');
  drupal_add_css(drupal_get_path('module', 'faze_quiz_course') . '/theme/faze_quiz_course_manage_course_student.css');
?>

  <?php
    
    
    print $faze_quiz_course_filter_table;
    if ($users){
      
      $rows = array();
      $i=0;
      foreach ($users as $student){
        $rows[$i]['class']="row_".$i." uid".$student->uid;
        
        $rows[$i]['data']['select']['data'] = "<input type='checkbox' class='user_select' value='".$student->uid."' />";
        
        $rows[$i]['data']['uid']['data'] = $student->uid;
        $rows[$i]['data']['uid']['class'] = "uid";
        
        $rows[$i]['data']['name']['data'] = $student->name;
        $rows[$i]['data']['name']['class'] = "name";
        
        global $user;
        $studetn_course=faze_quiz_course_get_course_by_techer_student($user->uid,$student->uid);
        $rows[$i]['data']['course']['data'] .= '<ul class="student_course">';
          $j=1;
          foreach ($studetn_course as $course){
            $class=array();
            $class[]='course';
            $class[]='cid_'.$course->cid;
            $class[]= ($j%2==0)? "even" : "odd";
            $rows[$i]['data']['course']['data'] .='<li class="'.implode(" ", $class).'">';
              $rows[$i]['data']['course']['data'] .='<a href="?cid='.$course->cid.'">'.$course->c_name."</a>";
            $rows[$i]['data']['course']['data'] .='</li> ';
            $j++;
          }
        $rows[$i]['data']['course']['data'] .= '</ul>';
        $rows[$i]['data']['course']['class'] = "student_course";
        
        $i++;
      }
      
      $attributes=array(
        id => "student_table",
      );
      print theme('table', $headers, $rows ,$attributes);
      print theme('pager', NULL, $limit, 0);
    }
    
  ?>

<!-- 
<form id="kol_modify" name="modify" method="post">
  <input class="form-submit" type="button" value="הוספת מילה" title="הוספת מילה" onclick="add_stop_word();" />
  <input class="form-submit" type="button" value="בדיקת הערה" title="בדיקת הערה" onclick="Stop_word_chack_commend();" />
  
  <input type="hidden" name="action_type" id="action_type" value="" />
  <input type="hidden" name="action_id" id="action_id" value="" />
  <input type="hidden" name="number_of_rows" id="edit_row" value="<?php echo $kol_request_counter ?>" />

</form>

 -->