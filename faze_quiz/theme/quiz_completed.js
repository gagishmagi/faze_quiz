$(document).ready(function() {
  $(".question .explanation_link>a").click(function() {
    $(this).parents(".question").find(".explanation").toggle(300);
    return false;
  }); 
});

