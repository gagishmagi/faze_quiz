$(function() {

  
  $('#student_table tbody tr').draggable( {
    containment: '#main',
    cursor: 'move',
    helper: dragStudentHelper,
    cursorAt: { left: 0, top: 0 },
    start: function( event, ui ) {$(this).addClass('ui-draggable-dragging')},
    stop: function( event, ui ) {$(this).removeClass('ui-draggable-dragging')},
  } );
  
  $('#block-views-course-block_1 .views-row').droppable( {
    drop: handleDropUserEvent,
    over: dragUserOver, 
    out: dragUserOut
  } );
  
  $('#student_table input.user_select').change(function() {
    var row=$(this).parents('tr');
    if (row.find('.user_select').is(':checked'))
      row.addClass('selected');
    else
      row.removeClass('selected');
  });
  
  $('#block-views-course-block_1').sticky({ 
    topSpacing: 20, 
    bottomSpacing: 100, 
    className: 'sticky', 
    wrapperClassName: 'my-wrapper' 
  });
  
});

function dragStudentHelper( event ) {
  if ($(this).find('.user_select').is(':checked'))
    return '<div id="draggable_helper">'+$('#student_table .user_select:checked').length+' תלמידים מסומנים</div>';
  else{
    var student=$(this).find("td.name").html();
    student=$.trim(student);
    if (student.length>10)
      student=student.substring(0, 9)+"...";
    //$(this).addClass('selected');
    return '<div id="draggable_helper">'+student+'</div>';
  }
}
  
function handleDropUserEvent( event, ui ) {
  var data = new Object();
  data.uid=new Array();
  var draggable = ui.draggable;
  if (draggable.find('.user_select').is(':checked'))
    $('#student_table input.user_select:checked').each(function(index) {
      data.uid.push($(this).val());
    });
  else{
    data.uid.push(draggable.find(".uid").html());
  }
  var droppable = $( this );
  data.cid=droppable.find(".views-field-cid .field-content").html();
  droppable.removeClass("student_over");
  dragUserOut( event, ui );
  $.ajax({
    url: '/manage_course_student/',
    //data: {action: "add_student", cid: cid, uid: uid },
    data: {action: "add_student", data: data },
    type: "POST",
  }).done(function ( data ) {
    data=jQuery.parseJSON(data);
    $.each(data.uid, function(index, uid) { 
      $('#student_table tbody tr.uid'+uid).find('.student_course ul.student_course')
        .append('<li class="course cid_'+data.cid+'"><a href="?cid='+data.cid+'">'+data.course_name+'</a></li>');
    });
    $('#student_table input.user_select:checked').attr('checked', false);
    $('#student_table tr.selected').removeClass('selected');
  });
}

function dragUserOver( event, ui ) {
  var droppable = $( this );
  droppable.addClass("student_over");
}

function dragUserOut( event, ui ) {
  var droppable = $( this );
  droppable.removeClass("student_over");
}