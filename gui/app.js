var gui    = require('nw.gui');
var fs       = require('fs');
var spawn    = require('child_process').spawn;
var exec     = require('child_process').exec;
var execSync = require('child_process').execSync;
var mkdirp   = require('mkdirp');
var ls       = require('ls');

var recorder = null;

var files = ls("./training/*");
var fl    = files.length;

$(document).ready(function() {

  $('#button').click(function() {
    if ($('#button').hasClass('recording')) {
      recorder.kill();
      exec("./feature tmp.wav tmp.feature");
      recorder = null;
      var result = [];
      var min = 0;
      for (var i=0; i<fl; i++) {
        var uri = "./training/"+files[i].name+"/data/";
        result[i] = 0;
        for (var j=1; j < 6; j++) {
          var path = uri + j + ".feature";
          result[i] = new Number(execSync("./distance tmp.feature "+path).toString(0));
        }
        result[i] /= 5;
        if (result[min] > result[i]) min = i;
      }
      var cmd = fs.readFileSync("./training/"+files[min].name+"/cmd").toString(0);
      exec(cmd);
    } else {
      recorder = spawn('sox',['-d','tmp.wav']);
    }
    $('#button').toggleClass('recording');
  });

  $('#menu').click(function() {
    if ($('#menu').hasClass('active')) {
      gui.Window.get().height = 70;
    } else {
      gui.Window.get().height = 300;
    }
    $('#menu').toggleClass('active');
  });

  $('#add').click(function () {
    var name = prompt('Name: ');
    var cmd  = prompt('Command: ');
    mkdirp.sync("./training/" + name + "/data");
    var uri = "./training/" + name + "/cmd";
    fs.closeSync(fs.openSync(uri, 'w'));
    fs.writeFileSync(uri, cmd);
    document.location.href = "./record_training.html#" + name;
  })
  for(var i=0; i < fl; i++) {
    $('#cmds').append("<div class='cmd'>"+files[i].name+"</div>");
  }
});
