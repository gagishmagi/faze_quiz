<?php
  $question_node=node_load($quiz_node->field_questions[$question_i][value], NULL, TRUE);
  $selected_answers=$quiz_node->field_answers[$question_i]['value'];
  $correct_answer=$question_node->field_correct_answer[0]['value'];
  $difficulty=$question_node->field_difficulty[0]['value'];
  $img_filepath=null;
  if ($question_node->field_quiz_image[0]!= null)
  {
    $img_filepath="/".$question_node->field_quiz_image[0]['filepath'];
  }
?>

<div id='question_<?php echo $question_i ?>' class='question <?php echo (($selected_answers==$correct_answer)? "correct_question":"wrong_question") ?>'>
  <div class='question_details'>
    <div class="copyright"></div>
    <div class='question_description'>
      <span class='num_of_question'><?php echo $question_i+1 ?>) </span>
      <?php echo $question_node->field_question[0]['value'] ?>
      <?php 
        if ($img_filepath)
          echo "<br /><img src='".$img_filepath."'/>"
      ?>
    </div>
  	<div class='difficulty'>רמת שאלה: <span class='difficulty_value_<?php echo get_difficulty_int($difficulty) ?>'><?php echo get_difficulty_str($difficulty)?></span></div>
  </div>
  <div class='answers'>
    <ul><?php 
      for ($i=0;$i<=4;$i++)
  	    echo "<li class='".(($correct_answer==$i)? "correct_answer":(($selected_answers==$i)? "wrong_selected_answer":""))."'>".$question_node->field_possible_answers[$i]['value']."</li>";
  	  echo "<li class='".(($selected_answers==-1)? "wrong_selected_answer":"")."'>".t("לא יודע")."</li>";
  	  ?>
    </ul>
  </div>
  <div class='explanation_link'><a href='#'>הצג הסבר</a></div>
  <div class='explanation'><?php echo $question_node->field_explanation[0]['value'] ?></div>
  <hr />
</div>