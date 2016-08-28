// NeoPixel Ring  RainbowSpin (c) 2016 Jonathan Lurie
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library



/*
 * Used by hls2rgb()
 */
float hue2rgb(float v1, float v2, float vH){
  float hue = vH;


  if(hue < 0){
    hue += 1;
  }

  if(hue > 1){
    hue -= 1;
  }

  if ( ( 6 * hue ) < 1 ) {
    return ( v1 + ( v2 - v1 ) * 6 * hue );
  }

  if ( ( 2 * hue ) < 1 ){
    return ( v2 );
  }

  if ( ( 3 * hue ) < 2 ){
    return ( v1 + ( v2 - v1 ) * ( ( 2 / 3 ) - hue ) * 6 );
  }

  return ( v1 );
}



/*
 * Convert a HSL color into RGB.
 * Note that h, l and s are defined on [0., 1.] while r, g and b are on [0, 255]
 */
void hls2rgb(float h, float l, float s, int* r, int* g, int* b){


  float rTemp = 0.;                   //RGB results from 0 to 255
  float gTemp = 0.;
  float bTemp = 0.;

  if ( s == 0 )                       //HSL from 0 to 1
  {
    rTemp = l;                   //RGB results from 0 to 255
    gTemp = l;
    bTemp = l;
  }
  else
  {
    float var_2 = 0.;

    if ( l < 0.5 ){
      var_2 = l * ( 1. + s );
    }else{
      var_2 = ( l + s ) - ( s * l );
    }

    float var_1 = 2 * l - var_2;

    rTemp = hue2rgb( var_1, var_2, h + ( 1. / 3. ) );
    gTemp = hue2rgb( var_1, var_2, h );
    bTemp = hue2rgb( var_1, var_2, h - ( 1. / 3. ) );
  }


  *r = rTemp * 255.;
  *g = gTemp * 255.;
  *b = bTemp * 255.;


}
