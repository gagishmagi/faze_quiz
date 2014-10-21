<?php
//dsm($techer_course);
  drupal_add_css(drupal_get_path('module', 'faze_quiz_course') . '/theme/faze_quiz_course_block.css');
?>

<?php if (count($techer_course)==0)
  echo t('אין מקצועים');
else 
{?>

<table>
  <thead>
    <tr>
      <th>שם מקצוע</th>
      <th>לדף מקצוע</th>
    </tr>
  </thead>
  <tbody>
  	<?php foreach ($techer_course as $course){
  	  print "<tr>";
  	  print "<td>".$course->name."</td>";
  	  print "<td><a href='/course/".$course->cid."'>לחץ</a></td>";
  	  }
  	?>
  </tbody>
</table>

<?php 
}
?>
