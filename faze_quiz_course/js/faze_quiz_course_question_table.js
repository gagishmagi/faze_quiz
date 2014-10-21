$(function() {
  question_table_init();
});

function question_table_init(){
  $("#question_table .short_question a,#question_table .nid a").click(
    function(e){
      e.preventDefault();
      var row=$(this).parents('tr');
   	  row.find('.full_question').toggle();
   	  row.find('.short_question').toggle();
    }
  );
}

//get row object and return the question nid
function getQuestionNid(row){
  var classs=$(row).prop("class").split(" ");
  var re = new RegExp('^q_nid');
  for (x in classs)
  {
    if (re.test(classs[x]))
    {
      return classs[x].replace(re,''); // remove the begining. 
    }
  }
  return null;
}

//get elmant with class like "sid_x" and return x.
function getSubjectSid(e){
  var classs=$(e).prop("class").split(" ");
  var re = new RegExp('^sid_');
  for (x in classs)
  {
    if (re.test(classs[x]))
    {
      return classs[x].replace(re,''); // remove the begining. 
    }
  }
  return null;
}
