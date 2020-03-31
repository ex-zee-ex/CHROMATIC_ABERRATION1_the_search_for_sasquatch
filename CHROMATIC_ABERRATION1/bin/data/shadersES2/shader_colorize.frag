precision highp float;


uniform sampler2D tex0;

varying vec2 texCoordVarying;

uniform float hue_select1;
uniform float saturation_amount1;
uniform float bright1;
uniform float hue1_theta;
uniform float hue1_amp;
uniform float bright1_theta;
uniform float bright1_amp;

uniform float hue_select2;
uniform float saturation_amount2;
uniform float bright2;
uniform float hue2_theta;
uniform float hue2_amp;
uniform float bright2_theta;
uniform float bright2_amp;

uniform float hue_select3;
uniform float saturation_amount3;
uniform float bright3;
uniform float hue3_theta;
uniform float hue3_amp;
uniform float bright3_theta;
uniform float bright3_amp;

uniform float hue_select4;
uniform float saturation_amount4;
uniform float bright4;
uniform float hue4_theta;
uniform float hue4_amp;
uniform float bright4_theta;
uniform float bright4_amp;

uniform int bright_switch1;
uniform int bright_switch2;
uniform int bright_switch3;
uniform int bright_switch4;

uniform float power;
uniform int glitch_switch3;

float oscillate(float theta,int shape){
    float osc=0.0;
    
    if(shape==0){
        osc=sin(theta);
    }
    
    //squarewave..can add a dc offset for pwm too?
    if(shape==1){
        osc=sign(sin(theta));
    }
    
    
    //haha tanwave
    //osc=tan(theta);
    
    //sawtooth??
    if(shape==2){
        osc=fract(theta/3.14);
    }
    
    
    
    return osc;
    
}


vec3 rgb2hsb(in vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));
    
    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsb2rgb(in vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}


void main()
{
    vec4 color=texture2D(tex0,texCoordVarying);
    
    vec3 color_hsb=rgb2hsb(vec3(color.r,color.g,color.b));
   
    int glitch_switch1=1;
    
    vec3 color_hsb1=vec3(hue_select1 + hue1_amp*oscillate(hue1_theta,0),saturation_amount1,color_hsb.z);
    vec3 color_hsb2=vec3(hue_select2 + hue2_amp*oscillate(hue2_theta,0),saturation_amount2,color_hsb.z);
    vec3 color_hsb3=vec3(hue_select3 + hue3_amp*oscillate(hue3_theta,0),saturation_amount3,color_hsb.z);
    vec3 color_hsb4=vec3(hue_select4 + hue4_amp*oscillate(hue4_theta,0),saturation_amount4,color_hsb.z);
    
    
    //color_hsb1.x+= hue_select1*color_hsb1.x;
    //color_hsb3.x+=fract(hue_select3*color_hsb3.x*color_hsb3.z*4*tan(color_hsb3.x*hue_select3*10));
    
    //will have to make a different variable for the hueselect3 here so that the glitch
    //remains
    //color_hsb3.x+=glitch_switch3*(color_hsb.x+hue_select3*fract(1000*sin(color_hsb3.x)));
    
    
    
    color_hsb1.z=fract(abs(color_hsb1.z+bright1+bright1_amp*oscillate(bright1_theta,0)));//*.33;
    color_hsb2.z=fract(abs(color_hsb2.z+bright2+bright2_amp*oscillate(bright2_theta,0)));
    color_hsb3.z=fract(abs(color_hsb3.z+bright3+bright3_amp*oscillate(bright3_theta,0)));
    color_hsb4.z=fract(abs(color_hsb4.z+bright4+bright4_amp*oscillate(bright4_theta,0)-.001));

    float color_hsb_original=color_hsb.z;
    
    //do i need to make this an float?
    //yes make power a float
    color_hsb.z=pow(color_hsb.z,power);
   // color_hsb.z=color_hsb.z*color_hsb.z*color_hsb.z;
    
   // color_hsb.z=sqrt(color_hsb.z);
    
    if(color_hsb.z<.33){
        color_hsb=mix(color_hsb1,color_hsb2,color_hsb.z*3.0);
    }
    
    if(color_hsb.z>.33 && color_hsb.z<.66){
        color_hsb=mix(color_hsb2,color_hsb3,(color_hsb.z-.33)*3.0);
    }
    
    if(color_hsb.z>.66){
        color_hsb=mix(color_hsb3,color_hsb4,(color_hsb.z-.66)*3.0);
    }
     
     
       color=vec4(hsb2rgb(vec3(color_hsb.r,color_hsb.g,color_hsb.b)),1.0);
    

    gl_FragColor =color;
}
