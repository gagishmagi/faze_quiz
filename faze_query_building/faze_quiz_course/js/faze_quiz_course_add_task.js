$(function() {
  $('fieldset.FixedQuestion_fieldset .fieldset-wrapper').append('<table id="FixedQuestion_table"><thead><tr><th>#</th><th>שאלה</th></tr></thead><tbody></tbody></table>');
  //$('<a href="#addQuestionBox" class="fancybox">הוספת שאלות</a>').appendTo('fieldset.FixedQuestion_fieldset .fieldset-wrapper');
  $('<a href="#addQuestionBox">הוספת שאלות</a>').appendTo('fieldset.FixedQuestion_fieldset .fieldset-wrapper');
  $('<div id="addQuestionBox" style="display:none;" class="question_select_table" ></div>').appendTo('fieldset.FixedQuestion_fieldset .fieldset-wrapper');
  showRandomQuestionSubject();
  /*$('.fancybox[href="#addQuestionBox"]').fancybox({
		width		: '80%',
		height		: '80%',
		autoSize	: false,
	    afterLoad   : function() {
	      showQuestionTable();
	    }
	});*/
  $( "#addQuestionBox" ).dialog({
    autoOpen: false,
    modal: true,
    buttons: {
      /*סיימתי: function() {
        $( this ).dialog( "close" );
      }*/
    },
    title:'הוספת שאלות',
    height: 400,
    width: 700,
  });
  $('[href="#addQuestionBox"]')
    .button()
    .click(function() {
      $( "#addQuestionBox" ).dialog( "open" );
      showQuestionTable();
      return false;
    });
  $('#edit-faze-quiz-course-addtask-course').change(showRandomQuestionSubject);
  
  $('#faze-quiz-course-addtask-form').submit(updateDataBeforeSubmit);
  
  //insart initialization value. whan edit or after unvalid from the server.
  var FixedQuestionJson=$.trim($('#edit-faze-quiz-course-addtask-FixedQuestion-nid').val());
  if (FixedQuestionJson!="" && FixedQuestionJson!='[]'){
    $.ajax({
      url: '/add_task',
      data: {action: "get_question_table", FixedQuestionJson: FixedQuestionJson },
      type: "POST",
      success: function(data) {
        $("<div>"+$.trim(data)+"</div>").find('#question_table tbody tr').each(function(){
          addQuestion(this);
        });
      },
    });
  }
  
});

function showQuestionTable(url){
  if (typeof url== 'undefined')
  {
    var cid=$('#edit-faze-quiz-course-addtask-course').val();
	  var url='/add_task?cid='+cid;
  }
  $.ajax({
	    url: url,
	    data: {action: "get_question_table"},
	    type: "POST",
	    success: function(data) {
	        //$('#addQuestionBox').html("<h3>הוספת שאלות</h3>"+data);
	        $('#addQuestionBox').html(data);
	        question_select_table_init();
	      },
	  });
}

function question_select_table_init(){
  question_table_init();
  $('#addQuestionBox .pager a'
		  +', #addQuestionBox #question_table thead a'
		  +', #addQuestionBox #question_table tbody li.subject a').click(
    function(e){
    	e.preventDefault();
    	showQuestionTable($(this).attr('href'));
    } 
  );
  $('#addQuestionBox #query_building-filter').submit(
	function(e){
	  e.preventDefault();
	  var cid=$('#edit-faze-quiz-course-addtask-course').val();
	  
	  var filter_search=$(this).find('[name=filter_search]').val();
	  var url='/add_task?cid='+cid+'&filter_search='+filter_search;
	  showQuestionTable(url);
	}	  
  );
  
  var fixedQuestion= new Array();
  $("#FixedQuestion_table tbody tr").each(function(){
    fixedQuestion.push(getQuestionNid(this));
  });
  
  $('#addQuestionBox #question_table tbody tr').each(function(){
    if ($.inArray(getQuestionNid(this),fixedQuestion)!=-1){
      $(this).find('td.question').append($('<span>השאלה הוספה</span>').addClass('existQuestion'));
    }
    else{
      $(this).find('td.question').append($('<a href="#addQuestion">הוסף שאלה</a>').button().addClass('addQuestion').click(addQuestionClick));
    }
  });
  //$('<a href="#addQuestion">הוסף שאלה</a>').addClass('addQuestion').click(addQuestionClick).appendTo('#addQuestionBox #question_table tbody td.question');
}

function addQuestionClick(e){
  e.preventDefault();
  var row=$(this).parents('tr');
  addQuestion(row);
  row.find('td.question .addQuestion').after($('<span>השאלה הוספה</span>').addClass('existQuestion')).remove();
}

function addQuestion(row){
  row=$(row);
  var newRow=$('<tr><td class="nid"></td><td class="question"></td></tr>');
  newRow.addClass('q_nid'+getQuestionNid(row));
  newRow.find('.nid').html(row.find('.nid').html());
  newRow.find('.question').html(row.find('.question').html());
  newRow.find('.question ul.question_subject li').each(function(){
    $(this).html($(this).find('a').html()); // remove the link from the subject.
  });
  newRow.find('.question .addQuestion').remove();
  newRow.find('ul.question_subject').remove();
  newRow.find('.short_question a, .nid a').click(function(e){
    e.preventDefault();
    var row=$(this).parents('tr');
    row.find('.full_question').toggle();
    row.find('.short_question').toggle();
  });
  $('<a href="#removeQuestion">הסר שאלה</a>').button().addClass('removeQuestion').click(removeQuestion).appendTo(newRow.find('.question'));
  $("#FixedQuestion_table tbody").append(newRow);
  
  updateSelectedQuestion();

}

function removeQuestion(e){
  e.preventDefault();
  var row=$(this).parents('tr');
  row.remove();
  updateSelectedQuestion();
}

function updateSelectedQuestion(){
  $(".FixedQuestion_fieldset legend.collapse-processed a").html('שאלות קבועות ('+$("#FixedQuestion_table tbody tr").length+')')
  $("#FixedQuestion_table tbody tr").removeClass(function(index) {
    var removeClass= "row-" + index+" ";
    removeClass += "row-" + (index+1)+" ";
    removeClass += "row-" + (index-1)+" ";
    removeClass += "odd even"
      return removeClass;
  });  
  $("#FixedQuestion_table tbody tr").addClass(function(index) {
    var addClass= "row-" + index+" ";
   if (index%2 == 0) 
     addClass+="odd";
   else
     addClass+="even";
   return addClass;
  });
}

var showRandomQuestionSubjectFirstCall=true;
function showRandomQuestionSubject(){
  var cid=$('#edit-faze-quiz-course-addtask-course').val();
  $('fieldset.randomQuestion_fieldset .fieldset-wrapper div.course').hide().removeClass('selected');
  if ($('fieldset.randomQuestion_fieldset .fieldset-wrapper div.cid-'+cid).length==0){
    var url='/add_task?cid='+cid;
    $.ajax({
        url: url,
        data: {action: "get_corse_subject_json"},
        type: "POST",
        success: function(data) {
          var elm=$('<div>').addClass("course cid-"+cid+" selected");
          obj = jQuery.parseJSON(data);
          $.each(obj.subject, function(i, val) {
            elm.append($("<span>").html(val.name+":"));
            elm.append($('<input>').addClass('subjectCountQuestion sid_'+val.sid).val("0")).change(updateRandomQuestion);
            elm.append($("<br />"));
          });
          $('fieldset.randomQuestion_fieldset .fieldset-wrapper').append(elm);
          if (showRandomQuestionSubjectFirstCall){
            //insart initialization value. whan edit or after unvalid from the server.
            var randomQuestionCount=jQuery.parseJSON($('#edit-faze-quiz-course-addtask-randomQuestion-sid').val());
            if (randomQuestionCount!=null){
              $.each(randomQuestionCount, function(index, value) { 
                $('input.subjectCountQuestion.sid_'+value.sid).val(value.count);
              });
              updateRandomQuestion();
            }
            showRandomQuestionSubjectFirstCall=false;
          }
        },
    });
  }
  else
    $('fieldset.randomQuestion_fieldset .fieldset-wrapper div.cid-'+cid).addClass('selected').show();
  updateRandomQuestion();
}

function updateRandomQuestion(){ 
  var count=0;
  $('fieldset.randomQuestion_fieldset .fieldset-wrapper div.selected input.subjectCountQuestion').each(function(){
    count+=parseInt(this.value);
  });
  $(".randomQuestion_fieldset legend.collapse-processed a").html('שאלות אקראיות ('+count+')')
}

function updateDataBeforeSubmit(e){
  //e.preventDefault();
  var ficedQuestion= new Array();
  $("#FixedQuestion_table tbody tr").each(function(){
    ficedQuestion.push({q_nid:getQuestionNid(this)});
  });
  $('#edit-faze-quiz-course-addtask-FixedQuestion-nid').val(JSON.stringify(ficedQuestion));
  
  var randomQuestion= new Array();
  $('fieldset.randomQuestion_fieldset .fieldset-wrapper div.selected input.subjectCountQuestion').each(function(){
    randomQuestion.push({sid:getSubjectSid(this),count:this.value});
  });
  $('#edit-faze-quiz-course-addtask-randomQuestion-sid').val(JSON.stringify(randomQuestion));
}
