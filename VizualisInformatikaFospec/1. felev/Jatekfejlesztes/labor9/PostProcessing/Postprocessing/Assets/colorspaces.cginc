#ifndef COLORSPACES_INC
#define COLORSPACES_INC

	float min3 (float r, float g, float b) {
		return min (r, min (g, b));
	}
	float max3 (float r, float g, float b) {
		return max (r, max (g, b));
	}

#ifndef F_EPSILON
#define F_EPSILON 0.0001f
#endif

	float3 rgb_to_hsv (float3 rgb)
	{ // HSV in [0,1]
	//http://www.easyrgb.com/index.php?X=MATH&H=20#text20
		
		float var_Min, var_Max, del_Max;
		float r=rgb.r; float g=rgb.g; float b=rgb.b;
		float h, s, v;
		var_Min = min3( r, g, b );
		var_Max = max3( r, g, b );
		del_Max = var_Max - var_Min;

		v = var_Max;
		
		if( del_Max == 0 )
		{
			h = 0;
			s = 0;
		}
		else
		{
			s = del_Max / var_Max;

			r = (((var_Max - r)/6.0) + (del_Max*0.5)) / del_Max;
			g = (((var_Max - g)/6.0) + (del_Max*0.5)) / del_Max;
			b = (((var_Max - b)/6.0) + (del_Max*0.5)) / del_Max;

			if ( abs(rgb.r-var_Max) < F_EPSILON )
				h = b - g;
			else if ( abs(rgb.g-var_Max) < F_EPSILON )
				h = 1/3.0 + r - b;
			else
				h = 2/3.0 + g - r;

			if( h < 0 )
				h += 1;
			if( h > 1 )
				h -= 1;
		}
		
		return float3(h, s, v);
	}

	float3 hsv_to_rgb (float3 hsv)
	{
		// http://www.easyrgb.com/index.php?X=MATH&H=21#text21
		int i;
		float h, s, v;
		float r, g, b;
		h = hsv.x;
		s = hsv.y;
		v = hsv.z;

		if ( s == 0 )
		{
			r = g = b = v;
		}
		else
		{
			h = h*6;
			if ( h == 6 ) h = 0;
			i = floor( h );
			float v1, v2, v3;
			v1 = v * (1 - s);
			v2 = v * (1 - s*(h-i));
			v3 = v * (1 - s*(1 - (h-i)));

			r = g = b = 0;
			if ( h < 1 )
			{
				r = v;
				g = v3;
				b = v1;
			}
			else if ( h < 2 )
			{
				r = v2;
				g = v;
				b = v1;
			}
			else if ( h < 3 )
			{
				r = v1;
				g = v;
				b = v3;
			}
			else if ( h < 4 )
			{
				r = v1;
				g = v2;
				b = v;
			}
			else if ( h < 5 )
			{
				r = v3;
				g = v1;
				b = v;
			}
			r = ( h >= 5 ) ? v : r;
			g = ( h >= 5 ) ? v1 : g;
			b = ( h >= 5 ) ? v2 : b;
		}
		return float3(r,g,b);
	}


	float3 rgb_to_hsl (float3 rgb)
	{ // HSL in [0,1]
	//http://www.easyrgb.com/index.php?X=MATH&H=18#text18
		
		float var_Min, var_Max, del_Max;
		float r=rgb.r; float g=rgb.g; float b=rgb.b;
		float h, s, l;
		var_Min = min3( r, g, b );
		var_Max = max3( r, g, b );
		del_Max = var_Max - var_Min;

		l = (var_Max + var_Min) / 2;
		
		if( del_Max == 0 )
		{
			h = 0;
			s = 0;
		}
		else
		{
			if ( l < 0.5f ) s = del_Max / ( var_Max + var_Min );
			else s = del_Max / ( 2 - var_Max - var_Min );

			r = (((var_Max - r)/6.0) + (del_Max*0.5)) / del_Max;
			g = (((var_Max - g)/6.0) + (del_Max*0.5)) / del_Max;
			b = (((var_Max - b)/6.0) + (del_Max*0.5)) / del_Max;

			if ( abs(rgb.r-var_Max) < F_EPSILON )
				h = b - g;
			else if ( abs(rgb.g-var_Max) < F_EPSILON )
				h = 1/3.0 + r - b;
			else
				h = 2/3.0 + g - r;

			if( h < 0 )
				h += 1;
			if( h > 1 )
				h -= 1;
		}
		
		return float3(h, s, l);
	}

	float hue_to_rgb( float v1, float v2, float vH )
	// http://www.easyrgb.com/index.php?X=MATH&H=19#text19
	{
		if ( vH < 0 ) vH += 1;
		else if ( vH > 1 ) vH -= 1;
		if ( ( 6 * vH ) < 1 ) return ( v1 + ( v2 - v1 ) * 6 * vH );
		if ( ( 2 * vH ) < 1 ) return ( v2 );
		if ( ( 3 * vH ) < 2 ) return ( v1 + ( v2 - v1 ) * ( ( 2.0f / 3.0f ) - vH ) * 6 );
		return ( v1 );
	}

	float3 hsl_to_rgb (float3 hsl)
	{
		// http://www.easyrgb.com/index.php?X=MATH&H=19#text19
		float h, s, l;
		float r, g, b;
		float var_1, var_2;
		h = hsl.x;
		s = hsl.y;
		l = hsl.z;

		if ( s == 0 )
		{
			r = g = b = l;
		}
		else
		{
			if ( l < 0.5 ) var_2 = l * ( 1 + s );
			else           var_2 = ( l + s ) - ( s * l );

			var_1 = 2 * l - var_2;

			r = hue_to_rgb( var_1, var_2, h + ( 1.0f / 3.0f ) ) ;
			g = hue_to_rgb( var_1, var_2, h );
			b = hue_to_rgb( var_1, var_2, h - ( 1.0f / 3.0f ) );
		}
		return float3(r,g,b);
	}
	
	float3 rgb_to_xyz( float3 rgb_vec )
	{
		float3x3 RGB2XYZ = {0.412453, 0.357580, 0.180423, 0.212671, 0.71516, 0.072169, 0.019334, 0.119193, 0.950227};
		return mul(RGB2XYZ, rgb_vec);
	}

	float3 xyz_to_rgb( float3 xyz_vec )
	{
		float3x3 XYZ2RGB = {3.240479, -1.537150, -0.498535, -0.969256, 1.875992, 0.041556, 0.055648, -0.204043, 1.057311};
		return mul(XYZ2RGB, xyz_vec);
	}

#endif