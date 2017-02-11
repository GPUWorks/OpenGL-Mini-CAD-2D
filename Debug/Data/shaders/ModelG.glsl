#version 430 core

layout(points) in;
layout(triangle_strip, max_vertices = 256) out;

#define CP_MAX_NO 20
#define CP_SIZE 3

//.............................. SSBO DATA ..............................

struct model_extra_data_t
{
	float dir_x;
	float dir_y;
	float dir_z;
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
uniform vec3 right;
uniform vec3 direction;
uniform vec3 up;

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

vec3 rotateY(vec3 punct, float u){
	float x = punct.x * cos(u) - punct.z *sin(u);
	float z = punct.x * sin(u) + punct.z *cos(u);
	return vec3(x, punct.y, z);
}

vec3 translateX(vec3 punct, float s){
	return vec3(punct.x, punct.y, punct.z + s);
}

vec3 translateWithDirectionvectorX(vec3 punct, float s) {
	vec3 r = vec3(model_extra_data[VertexIn[0].baseInstanceARB].dir_x * s, model_extra_data[VertexIn[0].baseInstanceARB].dir_y * s, model_extra_data[VertexIn[0].baseInstanceARB].dir_z * s);

	return (punct + r);
}

vec3 apply_transformation(vec3 punct, float us)
{
	if (model_extra_data[VertexIn[0].baseInstanceARB].transformation == 0)
		return translateWithDirectionvectorX(punct, us);
	else if (model_extra_data[VertexIn[0].baseInstanceARB].transformation == 1)
		return rotateY(punct, us);
}

//.............................. HERMITE CURVE ..............................


vec3 hermite(float t) {
	vec3 cp[CP_MAX_NO] = convert_cp();

	float u0 = 2 * t*t*t - 3 * t*t + 1;
	float u1 = -2 * t*t*t + 3 * t*t;
	float u2 = t*t*t - 2 * t*t + t;
	float u3 = t*t*t - t*t;

	return cp[0] * u0 + cp[2] * u1 + normalize(cp[1] - cp[0]) * u2 + normalize(cp[3] - cp[2]) * u3;
}


//.............................. BEZIER CURVE ..............................


vec3 bezier(float t) {
	vec3 cp[CP_MAX_NO] = convert_cp();

	return cp[0] * (1 - t)*(1 - t)*(1 - t) + cp[1] * 3 * t*(1 - t)*(1 - t) + cp[2] * 3 * t*t*(1 - t) + cp[3] *t*t*t;
}


//.............................. B-SPLINE CURVE ..............................


vec3 bspline(float t) {
	vec3 cp[CP_MAX_NO] = convert_cp();

	float u0 = (1 - t) * (1 - t);
	float u1 = -2 * t*t + 2 * t + 1;
	float u2 = t*t;

	return 0.5f * (cp[0] * u0 + cp[1] * u1 + cp[2] * u2);
}


//.............................. NURBS CURVE ..............................


vec3 nurbs(float t) {
	vec3 cp[CP_MAX_NO] = convert_cp();

	float w0, w1, w2;

	if (VertexIn[0].baseInstanceARB % 2 == 0)
	{
		w0 = 1.0; w1 = 0.5; w2 = 1.0;
	}
	else
	{
		w0 = 0.5; w1 = 1.0; w2 = 0.5;
	}

	float S = ((1 - t) * (1 - t)) * w0 + (-2 * t*t + 2 * t + 1) * w1 + (t*t) * w2;

	float u0 = (1 - t) * (1 - t) * w0;
	float u1 = (-2 * t*t + 2 * t + 1) * w1;
	float u2 = (t*t) * w2;

	return ((cp[0] * u0 + cp[1] * u1 + cp[2] * u2) / S);
}


//.............................. SPLINE CURVE ..............................


vec3 spline(float t) {
	vec3 cp[CP_MAX_NO] = convert_cp();

	float u0 = 2 * t*t*t - 3 * t*t + 1;
	float u1 = -2 * t*t*t + 3 * t*t;
	float u2 = t*t*t - 2 * t*t + t;
	float u3 = t*t*t - t*t;

	return cp[0] * u0 + cp[1] * u1 + 0.99 * normalize(cp[2]) * u2 + 0.99 * normalize(cp[3]) * u3;
}


//............................... GENERATOR ..................................

void generateCurves(int curve_type)
{
	int instance = VertexIn[0].baseInstanceARB;

	float offset = 1.0f / model_data[instance].curve_points_no;
	float tx = 0.2f;
	
	float curve_offset = VertexIn[0].instance * tx;
	int i;
	
	vec3 v1, v2, v3, v4;
		
	switch (curve_type)
	{
		case 1: {
			v1 = apply_transformation(hermite(0), curve_offset);
			break;
		}
		case 2: {
			v1 = apply_transformation(bezier(0), curve_offset);
			break;
		}
		case 4: {
			v1 = apply_transformation(bspline(0), curve_offset);
			break;
		}
		case 8: {
			v1 = apply_transformation(nurbs(0), curve_offset);
			break;
		}
		case 16: {
			v1 = apply_transformation(spline(0), curve_offset);
			break;
		}
	}
		
	v2 = apply_transformation(v1, tx);

	for (float t = offset; t < 1.0f + offset / 2.0; t += offset)
	{
		switch (curve_type)
		{
			case 1: {
				v3 = apply_transformation(hermite(t), curve_offset);
				break;
			}
			case 2: {
				v3 = apply_transformation(bezier(t), curve_offset);
				break;
			}
			case 4: {
				v3 = apply_transformation(bspline(t), curve_offset);
				break;
			}
			case 8: {
				v3 = apply_transformation(nurbs(t), curve_offset);
				break;
			}
			case 16: {
				v3 = apply_transformation(spline(t), curve_offset);
				break;
			}
		}

		v4 = apply_transformation(v3, tx);

		gl_Position = projection * view * vec4(v1, 1); EmitVertex();
		gl_Position = projection * view * vec4(v3, 1); EmitVertex();
		gl_Position = projection * view * vec4(v2, 1); EmitVertex();
		EndPrimitive();
		
		gl_Position = projection * view * vec4(v3, 1); EmitVertex();
		gl_Position = projection * view * vec4(v4, 1); EmitVertex();
		gl_Position = projection * view * vec4(v2, 1); EmitVertex();
		EndPrimitive(); 

		v1 = v3;
		v2 = v4;
	}
}


//.............................. MAIN ..............................

void main()
{
	int i = 0;

	int instance = VertexIn[0].baseInstanceARB;
	int cp_no = model_data[instance].control_points_no;
	vec3 cp[CP_MAX_NO] = convert_cp();
	

	if (VertexIn[0].instance < model_data[instance].curves_no - 1 && model_data[instance].curve_type < 32)
	{
		if (cp_no == 4)
		{
			generateCurves(model_data[instance].curve_type);
		}

		if (cp_no == 3)
		{
			generateCurves(model_data[instance].curve_type);
		}
	}
}