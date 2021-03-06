$fn=60;
//distance between the holes of the pcb
holeDistance=35.56;
//thickness of the walls
thickness=1.6;
//distance between hole centers and pcb edge
holeToPcb=3.81;
//distance between hole centers and wall exterior
holeToExt=holeToPcb+thickness;
//radious of PCB holes
holeRadius=1.6;
//height of the whole lid, from floor to top
height=8;
//layer height on the printer, I cannot tell exactly what I use this for
layerHeight=0.25;
//led screen variables
ledLength=8;
ledWidth=24.5;
ledX=2;
ledY=11;
//switch hole variables
switchHeight=4.6;
switchWidth=9;
switchX=14+holeToExt ;
switchY=holeToExt+holeDistance+holeToPcb;
//button hole variables
buttonRadius=5.5;
buttonX= 12.7+holeToExt;
buttonY=21.23+thickness;
//big connector hole variables
bigLength=holeToExt*1.2;
bigWidth=17.4;
bigX=holeToExt+holeDistance;
bigY=holeToExt+holeRadius+thickness;
//small connector hole variables
smallLength=11;
smallWidth=holeToExt*1.2;
smallX=holeToExt+holeRadius+thickness;
smallY=holeToExt+holeRadius+holeDistance;
//screw head holes variables
screwRadius=3;
screwHeight=3;
module exterior(){
    difference(){
        hull(){
        translate([holeToExt,holeToExt,0]) cylinder(r=holeToExt,h=height);
        translate([holeToExt,holeToExt+holeDistance,0]) cylinder(r=holeToExt,h=height);
        translate([holeToExt+holeDistance,holeToExt,0]) cylinder(r=holeToExt,h=height);
        translate([holeToExt+holeDistance,holeToExt+holeDistance,0]) cylinder(r=holeToExt,h=height);
        }
        translate ([holeToExt+holeDistance,holeToExt,0]) cornerCarve();
    }
}
module carve(){
    difference(){
  hull(){
    translate([holeToExt,holeToExt,0]) cylinder(r=holeToPcb,h=height);
   translate([holeToExt,holeToExt+holeDistance,0]) cylinder(r=holeToPcb,h=height);
   translate([holeToExt+holeDistance,holeToExt,0]) cylinder(r=holeToPcb,h=height);
   translate([holeToExt+holeDistance,holeToExt+holeDistance,0]) cylinder(r=holeToPcb,h=height);
    }
    translate ([holeToExt+holeDistance,holeToExt,0]) cornerCarveInt();
}
   
}
module support(){
difference(){
    union(){
        cylinder(r=holeRadius+thickness,h=height);
        translate([-holeToExt,0,0]) cube([holeToExt,holeRadius+thickness,height]);
         translate([0,-holeToExt,0]) cube([holeRadius+thickness,holeToExt,height]);
    }
translate([0,0,screwHeight+layerHeight])cylinder(r=holeRadius,h=height);
}
}
module cornerCarve() {
cylinder(r=holeRadius,h=height);
cube([holeToExt,holeRadius,height]);
translate([-holeRadius,-holeToExt-1,0]) cube([holeRadius+holeToExt,holeToExt+1,height]);
}
module cornerCarveInt() {
cylinder(r=holeRadius+thickness,h=height);
cube([holeToExt+thickness,holeRadius+thickness,height]);
translate([-(holeRadius+thickness),-(holeToExt+thickness+1),0]) cube([holeRadius+holeToExt+thickness,holeToExt+thickness+1,height]);
}
//we make the lid in here
difference(){
union(){
difference() {
    exterior();
    translate ([0,0,thickness]) carve();
    //led screen
    translate([ledX,ledY,0.5]) cube([ledLength,ledWidth,height]);
    //switch Hole
    translate([switchX,switchY,height-switchHeight]) cube([switchWidth,switchWidth,switchHeight]);
    //button Hole
    translate([buttonX,buttonY,-1]) cylinder(r=buttonRadius, h=height);
    //big connector hole
    translate([bigX,bigY,height-3]) cube([bigLength,bigWidth,height]);
    //small connector hole  
     translate([smallX,smallY,height-3]) cube([smallLength,smallWidth,height]);
    }
    //supports
    translate([holeToExt,holeToExt,0]) support();
    translate([holeToExt,holeToExt+holeDistance,0])  rotate([0,0,-90]) support();
    translate([holeToExt+holeDistance,holeToExt+holeDistance,0]) rotate([0,0,180]) support();
    
}
 //screw head holes
    translate([holeToExt,holeToExt,-1]) cylinder(r=screwRadius,h=screwHeight+1);
   
    translate([holeToExt+holeDistance,holeToExt+holeDistance,-1])  cylinder(r=screwRadius,h=screwHeight+1);
}
