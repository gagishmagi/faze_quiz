<?php
//dsm($techer_task);
  drupal_add_css(drupal_get_path('module', 'faze_quiz_course') . '/theme/faze_quiz_course_block.css');

?>

<?php if (count($student_task)==0)
  echo t('אין משימות');
else
{?>
<table>
  <thead>
    <tr>
      <th>משימה</th>
      <th>מקצוע</th>
      <th>נושא</th>
      <th>מצב</th>
      <td>תאריך יצירה</td>
    </tr>
  </thead>
  <tbody>
  	<?php foreach ($student_task as $task){
  	  print "<tr>";
  	  print "<td>".$task->title."</td>";
      print "<td>".$task->course_name."</td>";
      print "<td>".$task->subject_name."</td>";
  	  if ($task->q_nid==null)
  	    print "<td><a href='/quiz/addbytask/".$task->task_nid."'>טרם בוצע</a></td>";
  	  else if ($task->completed==FALSE)
  	    print "<td><a href='/quiz/".$task->q_nid."'>בביצוע</a></td>";
  	  else if($task->completed==TRUE)
  	    print "<td><a href='/quiz/".$task->q_nid."'>בוצע</a><br><a href='/quiz/addbytask/".$task->task_nid."'>מבחן נוסף</a></td>";
  	  print "<td>".date("d.m.y",$task->created)."</td>";
  	  print "</tr>";
   	  }
  	?>
  </tbody>
</table>
<?php
}
?>
