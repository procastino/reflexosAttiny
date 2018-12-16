$fn=60;
//distance between the holes of the pcb
holeDistance=35.56;
//tolerance for PCB carve, since the PDB doesn't fit well (quite a dirty fix)
tolerancePcb=0.2;
//thickness of the walls
thickness=1.6;
//distance between hole centers and pcb edge
holeToPcb=3.81;
//distance between hole centers and wall exterior
holeToExt=holeToPcb+thickness;
//radius of PCB holes
holeRadius=1.6;
//height of the whole bottom, from floor to top
height=14+thickness;

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
    translate([holeToExt,holeToExt,0]) cylinder(r=holeToPcb+tolerancePcb,h=height);
   translate([holeToExt,holeToExt+holeDistance,0]) cylinder(r=holeToPcb+tolerancePcb,h=height);
   translate([holeToExt+holeDistance,holeToExt,0]) cylinder(r=holeToPcb+tolerancePcb,h=height);
   translate([holeToExt+holeDistance,holeToExt+holeDistance,0]) cylinder(r=holeToPcb+tolerancePcb,h=height);
    }
    translate ([holeToExt+holeDistance,holeToExt,0]) cornerCarveInt();
    }
}

//carving the pcb hole   
module pcbCarve(){
    hull(){
    translate([holeToExt,holeToExt,0]) cylinder(r=holeToPcb,h=height);
   translate([holeToExt,holeToExt+holeDistance,0]) cylinder(r=holeToPcb,h=height);
   translate([holeToExt+holeDistance,holeToExt,0]) cylinder(r=holeToPcb,h=height);
   translate([holeToExt+holeDistance,holeToExt+holeDistance,0]) cylinder(r=holeToPcb,h=height);
    }
  }
  
module support(){
difference(){
    union(){
        cylinder(r=holeRadius+thickness,h=height);
        translate([-holeToExt,0,0]) cube([holeToExt,holeRadius+thickness,height]);
         translate([0,-holeToExt,0]) cube([holeRadius+thickness,holeToExt,height]);
    }
translate([0,0,thickness])cylinder(r=holeRadius,h=height);
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
    }
    
    translate([holeToExt,holeToExt,0]) support();
    translate([holeToExt,holeToExt+holeDistance,0])  rotate([0,0,-90]) support();
    translate([holeToExt+holeDistance,holeToExt+holeDistance,0]) rotate([0,0,180]) support();
}
 translate ([0,0,height-thickness]) pcbCarve();
}
