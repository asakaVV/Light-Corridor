#include "3D_tools.hpp"

/* Camera parameters and functions */
float theta = 0.1f;		 // Angle between x axis and viewpoint
float phy = 90.f;		 // Angle between z axis and viewpoint
float dist_zoom = 10.0f; // Distance between origin and viewpoint

struct v3d
{
	float x{0.f};
	float y{0.f};
	float z{0.f};

	v3d() : x(0.0), y(0.0), z(0.0)
	{
	}
	v3d(float in_x, float in_y, float in_z) : x(in_x), y(in_y), z(in_z)
	{
	}

	float length()
	{
		return sqrt(x * x + y * y + z * z);
	}
	void normalize()
	{
		float lg = this->length();
		x /= lg;
		y /= lg;
		z /= lg;
	}
	void cross(v3d b, v3d c)
	{
		this->x = b.y * c.z - b.z * c.y;
		this->y = c.x * b.z - c.z * b.x;
		this->z = b.x * c.y - b.y * c.x;
	}

	void display()
	{
		std::cout << "V :" << x << " / " << y << " / " << z << std::endl;
	}

	float dot(v3d a)
	{
		return (this->x * a.x + this->y * a.y + this->z * a.z);
	}
};

void setPerspective(float fovy, float a_ratio, float z_near, float z_far)
{
	float mat[16] = {0.0, 0.0, 0.0, 0.0,
					 0.0, 0.0, 0.0, 0.0,
					 0.0, 0.0, 0.0, 0.0,
					 0.0, 0.0, 0.0, 0.0};
	mat[0] = 1.0;
	mat[5] = 1.0;
	mat[10] = 1.0;
	mat[15] = 1.0;

	double f = 1.0 / tanf(double(fovy) * M_PI / (360.0f)); // 1/tan(fovy/2)
	mat[0] = f / a_ratio;
	mat[5] = f;
	mat[10] = -(z_far + z_near) / (z_far - z_near);
	mat[11] = -1.0f;
	mat[14] = -2.0f * z_far * z_near / (z_far - z_near);
	mat[15] = 0.0;

	glMultMatrixf(mat);
	// gluPerspective(fovy,a_ratio,z_near,z_far);
}

void setCamera()
{
	v3d eye{dist_zoom * cosf(toRad(theta)) * sinf(toRad(phy)),
			dist_zoom * sinf(toRad(theta)) * sinf(toRad(phy)),
			dist_zoom * cosf(toRad(phy))};

	// eye.display();
	v3d z_axis{cosf(toRad(theta)) * sinf(toRad(phy)),
			   sinf(toRad(theta)) * sinf(toRad(phy)),
			   cosf(toRad(phy))};
	z_axis.normalize();
	// z_axis.display();

	v3d up_axis{0., 0., 1.};
	v3d x_axis;
	x_axis.cross(up_axis, z_axis);
	x_axis.normalize();
	// x_axis.display();
	v3d y_axis;
	y_axis.cross(z_axis, x_axis);
	y_axis.normalize();
	// y_axis.display();

	float mat[16];
	mat[0] = x_axis.x;
	mat[4] = x_axis.y;
	mat[8] = x_axis.z;
	mat[12] = -1.0 * eye.dot(x_axis);

	mat[1] = y_axis.x;
	mat[5] = y_axis.y;
	mat[9] = y_axis.z;
	mat[13] = -1.0 * eye.dot(y_axis);

	mat[2] = z_axis.x;
	mat[6] = z_axis.y;
	mat[10] = z_axis.z;
	mat[14] = -1.0 * eye.dot(z_axis);

	mat[3] = 0.0;
	mat[7] = 0.0;
	mat[11] = 0.0;
	mat[15] = 1.0;

	glMultMatrixf(mat);
}

/* Convert degree to radians */
float toRad(float deg)
{
	return deg * M_PI / 180.0f;
}

void drawSquare()
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glEnd();
}

void drawCircle()
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 0.0);
	float step_rad = 2 * M_PI / (float)NB_SEG_CIRCLE;
	for (int i = 0; i <= NB_SEG_CIRCLE; i++)
	{
		glVertex3f(cos(i * step_rad), sin(i * step_rad), 0.0f);
	}
	glEnd();
}

void drawCircleFilaire()
{
	glBegin(GL_LINE_LOOP);
	float step_rad = 2 * M_PI / (float)NB_SEG_CIRCLE;
	for (int i = 0; i <= NB_SEG_CIRCLE; i++)
	{
		glVertex3f(cos(i * step_rad), sin(i * step_rad), 0.0f);
	}
	glEnd();
}

void drawCone()
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 1.0);
	float step_rad = 2 * M_PI / (float)NB_SEG_CIRCLE;
	for (int i = 0; i <= NB_SEG_CIRCLE; i++)
	{
		glVertex3f(cos(i * step_rad), sin(i * step_rad), 0.0f);
	}
	glEnd();
}

void drawSphere()
{
	float angle_theta{0.0};
	float angle_alpha{0.0};
	float pas_angle_theta{M_PI / NB_SEG_CIRCLE};
	float pas_angle_alpha{2 * M_PI / NB_SEG_CIRCLE};
	for (int band{0}; band < NB_SEG_CIRCLE; band++)
	{
		angle_alpha = 0.0;
		glBegin(GL_TRIANGLE_STRIP);
		for (int count{0}; count <= NB_SEG_CIRCLE; count++)
		{
			glVertex3f(cosf(angle_alpha) * sinf(angle_theta),
					   sinf(angle_alpha) * sinf(angle_theta),
					   cosf(angle_theta));
			glVertex3f(cosf(angle_alpha) * sinf(angle_theta + pas_angle_theta),
					   sinf(angle_alpha) * sinf(angle_theta + pas_angle_theta),
					   cosf(angle_theta + pas_angle_theta));
			angle_alpha += pas_angle_alpha;
		}
		glEnd();
		angle_theta += pas_angle_theta;
	}
}
