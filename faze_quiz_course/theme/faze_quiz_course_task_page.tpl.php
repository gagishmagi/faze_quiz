<?php
// $Id$
  drupal_add_css(drupal_get_path('module', 'faze_quiz_course') . '/theme/faze_quiz_course_task_page.css');
?>
<p><?php echo $node->body;?></p>
<h3>שאלות קבועות</h3>
<?php echo $FixedQuestionTable; ?>
	
	
<h3>שאלות אקראיות</h3>
<p>שאלות אקראיות שיוגרלו לתלמיד בהתאם לרמתו במקצוע</p>
<ul>
<?php
foreach ($randomQuestion as $subject)
  {
     print "<li>".$subject->name.': '.$subject->count."</li>"; 
  }
?>
</ul>


<h3>תלמידים</h3>
<table>
  <thead>
    <tr>
      <th>שם התלמיד</th>
      <th>מצב משימה</th>
    </tr>
  </thead>
  <tbody>
  	<?php foreach ($studentArray as $user){
  	  print "<tr>";
  	  print "<td>".$user->name."</td>";
  	  if ($user->q_nid==null)
  	    print "<td>טרם בוצע</td>";
  	  else if ($user->completed==FALSE)
  	    print "<td>בביצוע</td>";
  	  else 
  	    print "<td><a href='/quiz/".$user->q_nid."'>בוצע</a></td>";
  	  print "</tr>";
  	  }
  	?>
  </tbody>
</table>

<a href='/edit_task/<?php print $node->nid?>'>ערוך משימה</a>


  