$(function() {
  $('a.show_task_distribution_graf').click(function(){
    showTeskDistributionGraph($(this).parent().find('input.task_distribution_graf_data').val());
  })
  
});

function showTeskDistributionGraph(jsonData){
  var data=$.parseJSON(jsonData);
  alert(jsonData);
  var TeskDistributionGraph=new Array();
  var labels=new Array();
  

  
  var
  // Container div:
  container = document.getElementById("TeskDistributionGraphDiv"),
  // First data series:
  d1 = [],
  // A couple flotr configuration options:
  options =     {
    title : "123",
    bars : {
      show : true,
      horizontal : false,
      shadowSize : 0,
      barWidth : 0.5
    },
    mouse : {
      track : true,
      relative : true
    },
    yaxis : {
      min : 0,
      autoscaleMargin : 1
    },
    xaxis: {
      noTicks: 3,
    }
  },
  i, graph;

  var DataArr=[];
  jQuery.each(data, function(i, value){
    var range=value.range.split("-");
    DataArr[parseInt(range[0])+5]=[parseInt(range[0])+5,parseInt(value.count)];
  });
  
  
  for (i = 5; i <= 100; i += 10) {
    if( typeof DataArr[i] != "undefined" )  
      d1.push(DataArr[i]);
    else
      d1.push([i, 0]);
  }

  // Draw the graph:
  graph = Flotr.draw(
    container,  // Container element
    [ d1 ], // Array of data series
    options     // Configuration options
  );

} 