<?php
//dsm($techer_task);
  drupal_add_css(drupal_get_path('module', 'faze_quiz_course') . '/theme/faze_quiz_course_block.css');
?>

<?php if (count($techer_task)==0)
  echo t('אין משימות');
else 
{?>
<table>
  <thead>
    <tr>
      <th>משימה</th>
      <th>מקצוע</th>
      <th>נושא</th>
      <th>תאריך יצירה</th>
    </tr>
  </thead>
  <tbody>
  	<?php foreach ($techer_task as $task){
  	  print "<tr>";
  	  print "<td><a href='/task/".$task->task_nid."'>".$task->title."</a></td>";
      print "<td>".$task->course_name."</td>";
      print "<td>".$task->subject_name."</td>";
  	  print "<td>".date("d.m.y",$task->created)."</td>";
  	  }
  	?>
  </tbody>
</table>

<?php 
}
?>
