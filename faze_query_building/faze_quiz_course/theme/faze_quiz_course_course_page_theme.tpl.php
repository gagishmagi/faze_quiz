<?php
//$course,$studentArray,$taskArray
  faze_jquery_jquery();
  //faze_jquery_RGraph_bar_chart();
  faze_jquery_Flotr2_graph();
  drupal_add_js(drupal_get_path('module', 'faze_quiz_course') . '/js/faze_quiz_course_course_page.js');
  drupal_add_css(drupal_get_path('module', 'faze_quiz_course') . '/theme/faze_quiz_course_course_page.css');
  

?>

<h3>משימות</h3>
<div id='TeskDistributionGraphDiv'>
</div>
<?php if (count($taskArray)==0)
  echo t('אין משימות');
else 
{?>

<table>
  <thead>
    <tr>
      <th>שם משימה</th>
      <th>מספר תלמידים שסיימו</th>
      <th>ציון ממוצע</th>
      <th>גרף התפלגות</th>
    </tr>
  </thead>
  <tbody>
  	<?php foreach ($taskArray as $task){
  	  print "<tr>";
  	  print "<td><a href='/task/".$task->nid."'>".$task->title."</a></td>";
  	  print "<td>".$task->statistics->countQuiz."/".count($studentArray)."</td>";
  	  print "<td>".number_format($task->statistics->avrgGrade, 2, '.', '')."</td>";
  	  print "<td><a href='#distribution_graf_".$task->nid."' class='show_task_distribution_graf'>הצג</a><input class='task_distribution_graf_data' type='hidden' value='".json_encode($task->statistics->distribution)."'/></td>";
  	  print "</tr>";
  	  }
  	?>
  </tbody>
</table>


<?php 
}
?>
<a href='/add_task?cid=<?php print $course->cid;?>'>הוספת משימה</a>

<h3>תלמידים</h3>
<?php if (count($studentArray)==0)
  echo t('אין תלמידים');
else 
{?>

<table>
  <thead>
    <tr>
      <th>שם</th>
      <th>מספר מבחנים במקצוע</th>
      <th>ציון ממוצע</th>
    </tr>
  </thead>
  <tbody>
  	<?php foreach ($studentArray as $student){
  	  print "<tr>";
  	  print "<td>".$student->name."</td>";
  	  print "<td>".$student->statistics->countQuiz."</td>";
  	  print "<td>".number_format($student->statistics->avrgGrade, 2, '.', '')."</td>";
  	  print "</tr>";
  	  }
  	?>
  </tbody>
</table>

<?php 
}
?>
