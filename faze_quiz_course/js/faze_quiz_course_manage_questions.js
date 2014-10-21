$(function() {
  
  //open subject of course
  $(".view-course-subject .item-list li").hide();
  $(".view-course-subject .item-list h3").prepend('<span class="sign">◄</span>')
  var href="#"+ window.location.href.split('#')[1];
 // $('.view-course-subject .item-list a[href$="'+href+'"]').parent().parent().find("li").show();
 // $('.view-course-subject .item-list a[href$="'+href+'"]').parent().parent().find("h3 span.sign").html("▼");
 // $("#views-exposed-form-manage-questions-page-1").attr('action', href);
  
  $(".view-course-subject .item-list h3 a").toggle(function() {
    $(this).parent().parent().find("li").show("slow");
    $(this).parent().parent().find("h3 span.sign").html("▼");
    $("#views-exposed-form-manage-questions-page-1").attr('action', $(this).attr('href'));
  },
  function (){
    $(".view-course-subject .item-list li").hide("slow");
    $(".view-course-subject .item-list h3 span.sign").html("◄");
  });

  $('#question_table tbody tr').draggable( {
    containment: '#main',
    cursor: 'move',
    helper: dragQuestionHelper,
    cursorAt: { left: 0, top: 0 }
  } );
  
  $('#block-views-course_subject-block_1 .item-list .views-row').droppable( {
    drop: handleDropQuestionEvent,
    over: dragQuestionOver, 
    out: dragQuestionOut
  } );
  
  
  //open corse while hover when drag question.
  /*
  $('.view-course-subject .item-list').droppable( {
    over: function() {
      var href="#"+ window.location.href.split('#')[1];
      if(href!=$(this).find('a').attr('href')) 
        $(this).find("li").show("slow");
    }, 
    out: function() {
      var href="#"+ window.location.href.split('#')[1];
      if(href!=$(this).find('a').attr('href')) 
        $(this).find("li").hide("slow");
    }, 

  } );
  */
  
  $('#block-views-course_subject-block_1').sticky({ 
      topSpacing: 20, 
      bottomSpacing: 100, 
      className: 'sticky', 
      wrapperClassName: 'my-wrapper' 
  });
  
  
  //multiselect_widget - http://www.erichynds.com/jquery/jquery-ui-multiselect-widget/
  $("#query_building-filter select").multiselect({
    selectedText: "נבחר # מתוך #",
    noneSelectedText: 'בחר',
    selectedList: 4
  });
  
});


function dragQuestionHelper( event ) {
  var question=$(this).find(".short_question a").html();
  question=$.trim(question);
  if (question.length>20)
    question=question.substring(0, 19)+"...";
  return '<div id="draggable_helper">'+question+'</div>';
}
  
function handleDropQuestionEvent( event, ui ) {
  var draggable = ui.draggable;
  var qid=draggable.find(".nid a").html();
  var droppable = $( this );
  var sid=droppable.find(".views-field-sid .field-content").html();
  droppable.removeClass("question_over");
  dragQuestionOut( event, ui );
  $.ajax({
    //url: '/faze_quiz_course_add_question_to_subject/'+qid+'/'+sid,
    url: '/manage_questions/',
    data: {action: "add_quesion_to_corse", qid: qid, sid: sid },
    type: "POST",
  }).done(function ( data ) {
    data=jQuery.parseJSON(data);
    $('#question_table tbody tr.q_nid'+data.qid).find('.question ul.question_subject')
      .append('<li class="subject sid_'+data.sid+' cid_'+data.cid+'"><a href="?sid='+data.sid+'">'+data.course_name+'->'+data.subject_name+'</a></li>')
  });
}

function dragQuestionOver( event, ui ) {
  var droppable = $( this );
  droppable.addClass("question_over");
}

function dragQuestionOut( event, ui ) {
  var droppable = $( this );
  droppable.removeClass("question_over");
}


