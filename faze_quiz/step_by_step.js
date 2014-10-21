function SbsManager(wrapper , func_isStepValid) {
  this.steps = {};
  this.order = [];
  this.notValidStep = [];
  
  this.isStepValid = func_isStepValid;
  this.onComplit = null;
  this.onUnComplit = null;

  
  this.currentStep = null;
  this.currentStepNum = null;
  
  this._wrapper = $(wrapper);
  this._wrapper.append('<div id="sbs-navigation"><button type="button" id="sbs-prev-but" class="sbs-nav-button" onclick="sbs.prev()">הקודם</button><button type="button" id="sbs-next-but" class="sbs-nav-button" onclick="sbs.next()">הבא</button></div>');

  this.prevBut = $("#sbs-prev-but");
  this.nextBut = $("#sbs-next-but");
  //this.stepList = $("#sbs-step-list");

  this.addStep = function(stepSelector) {
    this.steps[stepSelector] = new SbsStep(stepSelector);
    this.order[this.order.length] = stepSelector;
    this.steps[stepSelector].isStepValid = this.isStepValid(this.steps[stepSelector]);
    if (this.steps[stepSelector].isStepValid==false)
      this.notValidStep.push(this.steps[stepSelector]);
  }

  this.start = function() {
    for (i in this.steps) {
      this.steps[i].obj.hide();
    }
    
    this._wrapper.find("input").change( function(){
      var newIsStepValid = sbs.isStepValid(sbs.currentStep);
      if (sbs.currentStep.isStepValid==newIsStepValid) return;
      sbs.currentStep.isStepValid=newIsStepValid;
      if (sbs.currentStep.isStepValid==true){
        //sbs.notValidStep.splice(sbs.notValidStep.indexOf(sbs.currentStep),1);  // indexOf don't work on IE8
        sbs.notValidStep.splice($.inArray(sbs.currentStep, sbs.notValidStep),1);
        if (sbs.onComplit && sbs.notValidStep==0)
          sbs.onComplit();
      }
      else{
        sbs.notValidStep.push(sbs.currentStep);
        if (sbs.onUnComplit && sbs.notValidStep==1)
          sbs.onUnComplit();
      }
      $('#sbs-nav-'+sbs.currentStepNum).removeClass("validStep notValidStep");
      $('#sbs-nav-'+sbs.currentStepNum).addClass(sbs.currentStep.isStepValid? "validStep": "notValidStep");
    })

    for (i in this.order) {
      this.nextBut.before("<button type='button' id='sbs-nav-"+i+"' class='sbs-nav-button' onclick='sbs.showStep("+i+");'>"+(parseInt(i,10)+1)+"</button>");
      $('#sbs-nav-'+i).addClass(this.steps[this.order[i]].isStepValid? "validStep": "notValidStep");
    } 
    
    
    this.showStep(0);
  }

  this.reOrder = function(arr) {
    this.order = arr;

    var newNum = 0;
    for (i = 0; i < arr.length; i++) {
      if (arr[i] == this.currentStep.id) {
        newNum = i;
        break;
      }
    }
    this.currentStepNum = newNum;
    this.showStep(newNum);
  }

  this.showStep = function(stepNum) {
    if (this.currentStepNum==stepNum) return;    
    
    if (this.currentStep){
      this.currentStep.obj.hide();
      $('#sbs-nav-'+this.currentStepNum).removeClass("showStep");
      if (this.currentStep.onEnd)
        this.currentStep.onEnd(this.currentStep);
    }
    
    this.currentStepNum = stepNum;
    this.currentStep = this.steps[this.order[stepNum]];
    this.currentStep.obj.show();
    
    if (stepNum == 0) {
      this.disableBut(this.prevBut);
    }
    else {
      this.enableBut(this.prevBut);
    }
    
    if (stepNum == this.order.length - 1) {
      //this.disableBut(this.nextBut);
      this.nextBut.html('סיים משימה');
    }
    else {
      //this.enableBut(this.nextBut);
      this.nextBut.html('הבא');
    }      
    
    $('#sbs-nav-'+this.currentStepNum).addClass("showStep");
    if (this.currentStep.onStart)
      this.currentStep.onStart(this.currentStep);
  }

  this.enableBut = function(obj) {
    obj.attr("className", "sbs-nav-button");
    obj.attr("disabled", false);
    obj.attr("type", "button");
  }

  this.disableBut = function(obj) {
    obj.attr("className", "sbs-nav-button disabled");
    obj.attr("disabled", true);
    obj.attr("type", "button");
  }
  
  this.next = function() {
    var StepNum = this.currentStepNum;
    if (StepNum == this.order.length - 1)
      this._wrapper.parents('form').submit();
    else if (StepNum < this.order.length - 1) {
      this.showStep(StepNum + 1);
    }
  }

  this.prev = function() {
    var num = this.currentStepNum;
    if (num > 0)
      this.showStep(num - 1);
  }

  this.addEvent = function(stepId, eventType, func) {
    if (eventType == "onStart") {
      this.steps[stepId].onStart = func;
    } else if (eventType == "onEnd") {
      this.steps[stepId].onEnd = func;
    }
  }
}

function SbsStep(stepSelector) {
  this.id = stepSelector;
  this.obj = $(stepSelector);
  this.onEnd = null;
  this.onStart = null;
  this.isStepValid = false;
}