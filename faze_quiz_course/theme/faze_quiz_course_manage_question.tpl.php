<?php
// $Id$
  drupal_add_js(drupal_get_path('module', 'faze_quiz_course') . '/js/jquery-ui-1.8.23.custom.min.js');
  drupal_add_js(drupal_get_path('module', 'faze_quiz_course') . '/js/faze_quiz_course_manage_questions.js');
  drupal_add_css(drupal_get_path('module', 'faze_quiz_course') . '/theme/faze_quiz_course_manage_questions.css');
?>

  <?php
    
    
    print $faze_quiz_course_filter_table;
    if ($question_nodes){
      
      $rows = array();
      $i=0;
      foreach ($question_nodes as $node){
        $rows[$i]['class']="row_".$i." q_nid".$node->nid;
        
        $rows[$i]['data']['nid']['data'] = '<a href="node/'.$node->nid.'">'.$node->nid.'</a>';
        $rows[$i]['data']['nid']['class'] = "nid";
        
        $rows[$i]['data']['question']['data'] = '<span class="short_question"><a href="node/'.$node->nid.'">'.trim(strip_tags($node->field_question[0]['value'])).'</a></span>';
        $rows[$i]['data']['question']['data'] .= '<span class="full_question">';
          $rows[$i]['data']['question']['data'] .= $node->field_question[0]['value'];
          $rows[$i]['data']['question']['data'] .= '<ul class="ans">';
            $j=0;
            foreach ($node->field_possible_answers as $answers)
            {
              if (!$answers || !$answers['value'] ) break;
              $class=array();
              $class[]='ans_'.$j;
              $class[]= ($j%2==0)? "odd" : "even";
              if ($node->field_correct_answer[0]['value']==$j)
                $class[]="correct_ans";
              $rows[$i]['data']['question']['data'] .='<li class="'.implode(" ", $class).'">';
                $rows[$i]['data']['question']['data'] .=$answers['value'];
              $rows[$i]['data']['question']['data'] .='</li>';
              $j++;
            }
          $rows[$i]['data']['question']['data'] .= '</ul>';
        $rows[$i]['data']['question']['data'] .= '</span>';
        global $user;
        $question_subject=faze_quiz_course_get_question_subject($node->nid,$user->uid);
        $rows[$i]['data']['question']['data'] .= '<ul class="question_subject">';
          $j=1;
          foreach ($question_subject as $subject){
            $class=array();
            $class[]='subject';
            $class[]='sid_'.$subject->sid;
            $class[]='cid_'.$subject->cid;
            $class[]= ($j%2==0)? "even" : "odd";
            $rows[$i]['data']['question']['data'] .='<li class="'.implode(" ", $class).'">';
              $rows[$i]['data']['question']['data'] .='<a href="?sid='.$subject->sid.'">'.$subject->c_name."->".$subject->s_name."</a>";
            $rows[$i]['data']['question']['data'] .='</li> ';
            $j++;
          }
        $rows[$i]['data']['question']['data'] .= '</ul>';
        $rows[$i]['data']['question']['class'] = "question";
        
        $subject=array_shift(array_values($node->taxonomy));
        $rows[$i]['data']['subject']['data'] = "<a href='?filter_term_node_tid[]=".$subject->tid."'>".$subject->name."</a>";
        $rows[$i]['data']['subject']['class'] = "subject subject_".$subject->name." subject_".$subject->tid;
        
        $rows[$i]['data']['difficulty']['data'] =round($node->field_difficulty[0]['value'],2);
        $rows[$i]['data']['difficulty']['class'] = "difficulty";
        
        $rows[$i]['data']['u_name']['data'] = "<a href='?filter_users_uid[]=".$node->uid.	"'>".$node->name."</a>";
        $rows[$i]['data']['u_name']['class'] = "u_name u_name_".$node->name." u_name_".$node->uid;
        
        $i++;
      }
      
      $attributes=array(
        id => "question_table",
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