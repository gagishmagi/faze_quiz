<?php
  $module_path = drupal_get_path('module', 'faze_quiz');
  drupal_add_css($module_path .'/theme/quiz_completed.css');
  drupal_add_js($module_path .'/theme/quiz_completed.js');
  
  drupal_set_title("תוצאות");
?>

<div id="quiz_header">
  <div id="title">תוצאות</div>
  <div id="difficulty">רמת המבחן <span class='difficulty_value_<?php echo get_difficulty_int($quiz_node->field_difficulty[0]['value']) ?>'><?php echo get_difficulty_str($quiz_node->field_difficulty[0]['value']) ?></span></div>
</div>

<p><?php echo "ענית נכון על " . $quiz_node->field_count_correct[0]['value'] . " מתוך ".count($quiz_node->field_questions)." שאלות"?></p>

<?php
  for($i=0;$i<sizeof($quiz_node->field_questions);$i++){
    echo theme('faze_quiz_completed_question', $quiz_node,$i);
  }
  
?>

<a href='/'>חזרה לדף הראשי</a>