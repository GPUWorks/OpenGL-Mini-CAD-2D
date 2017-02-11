#version 430 core

layout(points) in;
layout(points, max_vertices = 146) out;


#define CP_MAX_NO 20
#define CP_SIZE 3

//.............................. SSBO DATA ..............................

struct model_extra_data_t
{
	float right_x;
	float right_y;
	float right_z;
	int transformation;
};

layout (std430, binding = 1) buffer model_extra_data_ssbo
{
	model_extra_data_t model_extra_data[];
};


struct model_data_t
{
	//int texture_id;
	int curve_type;
	int curves_no;
	int curve_points_no;
	int control_points_no;
	float control_points[CP_MAX_NO * CP_SIZE];
};

layout (std430, binding = 0) buffer model_data_ssbo
{
	model_data_t model_data[];
};

//.............................. UNIFORM DATA ..............................

uniform mat4 view;
uniform mat4 projection;

//.............................. VERTEX PASSED DATA ..............................

in VertexData {
    vec2 texCoord;
    vec3 normal;
	int baseInstanceARB;
	int instance;
} VertexIn[];
 
out VertexData {
    vec2 texCoord;
    vec3 normal;
	flat int baseInstanceARB;
	flat vec3 color;
} VertexOut;


//.........................................................................
//.............................. COMPUTATION ..............................
//.........................................................................


//.............................. HELPERS ..............................

vec3[CP_MAX_NO] convert_cp()
{
	int i = 0, j = 0;
	int cp_no = model_data[VertexIn[0].baseInstanceARB].control_points_no;
	float cp[CP_MAX_NO * CP_SIZE] = model_data[VertexIn[0].baseInstanceARB].control_points;

	vec3 cpv[CP_MAX_NO];

	for (i = 0; i < cp_no; i++)
	{
		cpv[i].x = cp[j++];
		cpv[i].y = cp[j++];
		cpv[i].z = cp[j++];
	}

	return cpv;
}


//.............................. MAIN ..............................

void main()
{
	int i = 0;

	int instance = VertexIn[0].baseInstanceARB;
	int cp_no = model_data[instance].control_points_no;
	vec3 cp[CP_MAX_NO] = convert_cp();


	switch (model_data[instance].curve_type)
	{
		case 1: { // hermite
			for(i = 0; i < cp_no && model_data[instance].curve_type != 256; i++)
			{
				vec4 p = vec4(cp[i], 1.0);

				if (i == 1 || i == 3)
					VertexOut.color = vec3(0.0, 1.0, 1.0);
				else
					VertexOut.color = vec3(0.0, 0.0, 0.0);

				gl_Position = projection * view * p;

				EmitVertex();
				EndPrimitive();
			}

			break;
		}
		case 2: { // bezier
			for(i = 0; i < cp_no && model_data[instance].curve_type != 256; i++)
			{
				vec4 p = vec4(cp[i], 1.0);

				if (i == 3 || i == 0)
					VertexOut.color = vec3(0.0, 1.0, 1.0);
				else
					VertexOut.color = vec3(0.0, 0.0, 0.0);

				gl_Position = projection * view * p;

				EmitVertex();
				EndPrimitive();
			}

			break;
		}
		case 4: { // bspline
			VertexOut.color = vec3(0.0, 0.0, 0.0);

			for(i = 0; i < cp_no && model_data[instance].curve_type != 256; i++)
			{
				vec4 p = vec4(cp[i], 1.0);
				gl_Position = projection * view * p;

				EmitVertex();
				EndPrimitive();
			}

			break;
		}
		case 8: { // nurbs
			VertexOut.color = vec3(0.0, 0.0, 0.0);

			for(i = 0; i < cp_no && model_data[instance].curve_type != 256; i++)
			{
				vec4 p = vec4(cp[i], 1.0);
				gl_Position = projection * view * p;

				EmitVertex();
				EndPrimitive();
			}

			break;
		}
		case 16: { // spline
			VertexOut.color = vec3(0.0, 0.0, 0.0);

			for(i = 0; i < cp_no && model_data[instance].curve_type != 256; i++)
			{
				if (i > 1)
					return;

				vec4 p = vec4(cp[i], 1.0);
				gl_Position = projection * view * p;

				EmitVertex();
				EndPrimitive();
			}
	
			break;
		}

		case 32: { // bezier surface
			VertexOut.color = vec3(0.0, 0.0, 0.0);

			for(i = 0; i < cp_no && model_data[instance].curve_type != 256; i++)
			{
				vec4 p = vec4(cp[i], 1.0);
				gl_Position = projection * view * p;

				EmitVertex();
				EndPrimitive();
			}
	
			break;
		}

		case 64: { // spline surface
			VertexOut.color = vec3(0.0, 0.0, 0.0);

			for(i = 0; i < cp_no && model_data[instance].curve_type != 256; i++)
			{
				vec4 p = vec4(cp[i], 1.0);
				gl_Position = projection * view * p;

				EmitVertex();
				EndPrimitive();
			}
	
			break;
		}

		case 128: { // nurbs surface
			VertexOut.color = vec3(0.0, 0.0, 0.0);

			for(i = 0; i < cp_no && model_data[instance].curve_type != 256; i++)
			{
				vec4 p = vec4(cp[i], 1.0);
				gl_Position = projection * view * p;

				EmitVertex();
				EndPrimitive();
			}
	
			break;
		}
	}
	
}