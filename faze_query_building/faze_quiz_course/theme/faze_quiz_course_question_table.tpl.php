<?php
// $Id$
  drupal_add_css(drupal_get_path('module', 'faze_quiz_course') . '/theme/faze_quiz_course_question_table.css');
  drupal_add_js(drupal_get_path('module', 'faze_quiz_course') . '/js/faze_quiz_course_question_table.js');
?>

  <?php
    
    
    print $faze_quiz_course_filter_table;
    if ($question_nodes){
      
      $rows = array();
      $i=0;
      foreach ($question_nodes as $node){
        $rows[$i]['class']="row_".$i." q_nid".$node->nid;
        if (in_array("nid", $table_col)){
          $rows[$i]['data']['nid']['data'] = '<a href="node/'.$node->nid.'">'.$node->nid.'</a>';
          $rows[$i]['data']['nid']['class'] = "nid";
        }
        if (in_array("question", $table_col)){
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
        }
        if (in_array("subject", $table_col)){
          /*$subject=array_shift(array_values($node->taxonomy));
          $rows[$i]['data']['subject']['data'] = "<a href='?filter_term_node_tid[]=".$subject->tid."'>".$subject->name."</a>";
          $rows[$i]['data']['subject']['class'] = "subject subject_".$subject->name." subject_".$subject->tid;*/
          $rows[$i]['data']['subject']['data'] = "<a href='?filter_faze_quiz_course_course_cid[]=".$subject->cid."'>".$subject->c_name."</a>";
          $rows[$i]['data']['subject']['class'] = "subject subject_".$subject->c_name." subject_".$subject->cid;
        }
        if (in_array("difficulty", $table_col)){
          $rows[$i]['data']['difficulty']['data'] =round($node->field_difficulty[0]['value'],2);
          $rows[$i]['data']['difficulty']['class'] = "difficulty";
        }
        if (in_array("u_name", $table_col)){
          $rows[$i]['data']['u_name']['data'] = "<a href='?filter_users_uid[]=".$node->uid.	"'>".$node->name."</a>";
          $rows[$i]['data']['u_name']['class'] = "u_name u_name_".$node->name." u_name_".$node->uid;
        }
        $i++;
      }
      
      $attributes=array(
        id => "question_table",
      );
      print theme('table', $headers, $rows ,$attributes);
      print theme('pager', NULL, $limit, 0);
    }
    
  ?>
