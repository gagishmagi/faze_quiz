function isStepValid(sbsStep){
  return sbsStep.obj.find(".form-radios input:checked").length>0;
}

$("h1.title").after("<div id='quiz_header'><div id='question_num'></div><div id='timer'><p>זמן לסיום המבחן</p><p><span id='left_time'></span></p></div></div>");
$("#content-area").prepend("<div id='break'><button id='toggleBreak'></button></div>");
$("#faze-quiz-quiz-form>div").append("<div id='break_msg'><h1>הפסקה</h1><a href='/'>חזרה לדף הראשי</a></div>");
$('#break_msg').hide();

var endQuizTime=parseInt(new Date().getTime()*0.001,10)+2.5*3600;
var startBreakTIme = null;
var startQuestionTime=null;

function two_digit(x){
  if (x<10)
    return "0"+x;
  return x;
}

function showTimeLeft(){
  if (startBreakTIme) return;
  var now=parseInt(new Date().getTime()*0.001,10);
  var timeLeft=endQuizTime-now;
  
  var seconds = timeLeft%60;
  timeLeft-=seconds;
  timeLeft/=60;
  var minutes = timeLeft%60;
  timeLeft-=minutes;
  timeLeft/=60;
  var hours = timeLeft;
  
  $("#left_time").html(hours+":"+two_digit(minutes)+":"+two_digit(seconds));
  
  if(endQuizTime<=now){
    $("#left_time").html("תם הזמן");
    alert("נגמר זמן הבחינה");
  }
  else if (!startBreakTIme)
    window.setTimeout(showTimeLeft, 1000);
}

showTimeLeft();

$("#toggleBreak").click(toggleBreak);


function toggleBreak(){
  if (!startBreakTIme)
  {
    startBreakTIme=parseInt(new Date().getTime()*0.001,10);
    $("#startBreak").hide();
    $("#endBreak").show();
    $("#content-area input:radio").attr('disabled', 'disabled');
    $("#sbs-navigation .sbs-nav-button").attr('disabled', 'disabled');
    $("#content .section").addClass("quizBreak");
    $('.fieldset_question').hide();
    $('#break_msg').show();
  }
  else
  {
    var now=parseInt(new Date().getTime()*0.001,10);
    var breakTime=now-startBreakTIme;
    endQuizTime+=breakTime;
    startQuestionTime+=breakTime;
    startBreakTIme=null;
    showTimeLeft();
    $("#endBreak").hide();
    $("#startBreak").show();
    $("#content-area input:radio").removeAttr('disabled');
    $("#sbs-navigation .sbs-nav-button").removeAttr('disabled', 'disabled');
    $("#sbs-navigation .sbs-nav-button.disabled").attr('disabled', 'disabled');
    $("#content .section").removeClass("quizBreak");
    //$('.fieldset_question').hide();
    sbs.currentStep.obj.show();
    $('#break_msg').hide();
  }
  return false;
}

function quiz_on_start_question(sbsStep){
  startQuestionTime = parseInt(new Date().getTime()*0.001,10);
  $("#question_num").html(sbsStep.obj.find("legend").html());
}

function quiz_on_end_question(sbsStep){
  var old_time = parseInt(sbsStep.obj.find(".fieldset_time").val(),10);
  var now=parseInt(new Date().getTime()*0.001,10)
  sbsStep.obj.find(".fieldset_time").val(old_time+now-startQuestionTime);
}


var sbs = new SbsManager("#faze-quiz-quiz-form>div",isStepValid);
$('.fieldset_question').each(function(index) {
  var question_selector="#"+this.id;
  sbs.addStep(question_selector);
  sbs.addEvent(question_selector, "onStart", quiz_on_start_question);
  sbs.addEvent(question_selector, "onEnd", quiz_on_end_question);
});

//sbs.onComplit = function(){$("#edit-submit").attr("disabled", false);}
//$("#edit-submit").attr("disabled", true);
isComplit=false;
sbs.onComplit = function(){isComplit=true;}
sbs.onUnComplit = function(){isComplit=false;}


$("#faze-quiz-quiz-form").submit(function(){
  if(!isComplit){
    if (confirm("לא סיימת את המבחן, להגיש בכל זאת?"))
      {
        for (step in sbs.notValidStep){
          $(sbs.notValidStep[step].obj).find(".form-item:last input").attr('checked', true);
        }
      }
    else return false;
  }
  quiz_on_end_question(sbs.currentStep);
  return true;
});

sbs.start();
