boxHeight=150;
boxWidth=130;

difference(){
    square([ boxWidth , boxHeight ] , center=true );
    translate([0, (boxHeight/2) - 40 ])square([71,38] , center=true );
    //translate([0, (boxHeight/2) - 40 ])square([93,70] , center=true );
}

