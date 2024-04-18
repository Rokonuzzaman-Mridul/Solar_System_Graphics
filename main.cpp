#include <GL/glut.h> // Include the GLUT library for OpenGL
#include <cmath> // Include the cmath library for mathematical functions

#define PI 3.14159265358979323846 // Define the value of PI

float angle = 120.0f; // Declare and initialize the angle variable for animation

// Define the CelestialBody class to represent celestial bodies
class CelestialBody
{
public:
    // Constructor to initialize celestial body properties
    CelestialBody(float radius, float distance, float orbitSpeed, float rotationSpeed, float ringRadius, float r, float g, float b)
        : radius(radius), distance(distance), orbitSpeed(orbitSpeed), rotationSpeed(rotationSpeed), ringRadius(ringRadius), r(r), g(g), b(b) {}

    // Method to draw the orbit path of the celestial body
    void drawOrbit() const
    {
        glColor3f(0.5f, 0.5f, 0.5f); // Set color for the orbit path
        glBegin(GL_LINE_LOOP); // Begin drawing a line loop
        for (int i = 0; i < 360; i++)
        {
            float radian = i * PI / 180.0; // Convert angle to radians
            glVertex3f(distance * cos(radian), 15.0f, distance * sin(radian)); // Plot points on the orbit path
        }
        glEnd(); // End drawing the line loop
    }

    // Method to draw the celestial body
    void draw() const
    {
        glPushMatrix(); // Save the current matrix
        glRotatef(angle * orbitSpeed, 0.0f, 1.0f, 0.0f); // Rotate around the sun (y-axis)
        glTranslatef(distance, 15.0f, 0.0f); // Translate to the position of the celestial body
        glRotatef(angle * rotationSpeed, 0.0f, 1.0f, 0.0f); // Rotate the celestial body around its axis

        glColor3f(r, g, b); // Set color for the celestial body
        glutSolidSphere(radius, 50, 50); // Draw a solid sphere representing the celestial body

        glPopMatrix(); // Restore the previous matrix
    }

    // Method to draw the moon of a celestial body
    void drawMoon(const CelestialBody& earth) const
    {
        glPushMatrix(); // Save the current matrix
        glRotatef(angle * rotationSpeed, 0.0f, 1.0f, 0.0f); // Rotate around its axis

        // Draw the moon relative to the earth's position
        glTranslatef(earth.distance, 0.0f, 0.0f); // Move to the earth's position
        glRotatef(angle * orbitSpeed * 0.3f, 0.0f, 1.0f, 0.0f); // Adjusted moon's orbit speed for better visualization
        glTranslatef(distance, 15.0f, 0.0f); // Move to the correct orbit distance from the earth

        glColor3f(r, g, b); // Set color for the moon
        glutSolidSphere(radius, 50, 50); // Draw a solid sphere representing the moon

        glPopMatrix(); // Restore the previous matrix
    }

    // Method to draw Saturn with its rings
    void drawSaturn() const
    {
        glPushMatrix(); // Save the current matrix
        glRotatef(angle * orbitSpeed, 0.0f, 1.0f, 0.0f); // Rotate around the sun (y-axis)
        glTranslatef(distance, 15.0f, 0.0f); // Translate to the position of Saturn
        glRotatef(angle * rotationSpeed, 0.0f, 0.5f, 0.5f); // Rotate Saturn around its axis

        // Draw rings if there are any
        if (ringRadius > 0.0f) {
            glColor3f(0.7f, 0.7f, 0.7f); // Set color for the rings
            glutSolidTorus(ringRadius, radius * 1.2f, 2, 100); // Draw the rings
        }

        glColor3f(r, g, b); // Set color for Saturn
        glutSolidSphere(radius, 50, 50); // Draw a solid sphere representing Saturn

        glPopMatrix(); // Restore the previous matrix
    }

private:
    float radius; // Radius of the celestial body
    float distance; // Distance from the sun
    float orbitSpeed; // Speed of orbiting around the sun
    float rotationSpeed; // Speed of rotation around its axis
    float ringRadius; // Radius of the rings (0 if none)
    float r, g, b; // Color components (r, g, b)
};

// Initialize instances of CelestialBody for various celestial objects
CelestialBody sun(12.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
CelestialBody mercury(1.0f, 15.0f, 4.0f, 1.5f, 0.0f, 0.8f, 0.4f, 0.2f);
CelestialBody venus(1.5f, 20.0f, 2.5f, 1.0f, 0.0f, 0.9f, 0.6f, 0.3f);
CelestialBody earth(1.5f, 25.0f, 1.0f, 1.0f, 0.0f, 0.2f, 0.5f, 1.0f);
CelestialBody moon(0.3f, 2.0f, 9.0f, 1.0f, 0.0f, 0.8f, 0.8f, 0.8f);
CelestialBody mars(1.5f, 30.0f, 0.9f, 1.5f, 0.0f, 0.78f, 0.29f, 0.11f);
CelestialBody jupiter(4.5f, 40.0f, 1.0f, 2.0f, 0.0f, 1.0f, 0.5f, 0.0f);
CelestialBody saturn(3.0f, 50.0f, 0.5f, 1.0f, 0.5f, 0.3f, 0.27f, 0.18f); // Specify ring radius (0.5f in this case)
CelestialBody uranus(1.6f, 55.0f, 1.5f, 1.5f, 0.0f, 0.1f, 0.29f, 0.11f);
CelestialBody neptune(1.4f, 60.0f, 1.9f, 1.5f, 0.0f, 0.78f, 0.0f, 0.11f);

// Function to draw the entire solar system
void drawSolarSystem()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers

    glLoadIdentity(); // Load the identity matrix
    gluLookAt(0.0f, 30.0f, 70.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // Set up the camera position and orientation

    // Draw each celestial body and its orbit
    sun.draw();
    mercury.drawOrbit();
    mercury.draw();
    venus.drawOrbit();
    venus.draw();
    earth.drawOrbit();
    earth.draw();
    moon.drawOrbit();
    moon.drawMoon(earth);
    mars.drawOrbit();
    mars.draw();
    jupiter.drawOrbit();
    jupiter.draw();
    saturn.drawOrbit();
    saturn.drawSaturn();
    uranus.drawOrbit();
    uranus.draw();
    neptune.drawOrbit();
    neptune.draw();

    glFlush(); // Flush the OpenGL command pipeline
}

// Function to update the animation
void update(int value)
{
    angle += 0.5f; // Increment the angle for animation
    glutPostRedisplay(); // Mark the current window as needing to be redisplayed
    glutTimerFunc(16, update, 0); // Set the timer for the next update
}

// Function to handle window resizing
void reshape(int w, int h)
{
    glViewport(0, 0, w, h); // Set the viewport to the entire window
    glMatrixMode(GL_PROJECTION); // Set the matrix mode to projection
    glLoadIdentity(); // Load the identity matrix
    gluPerspective(90.0f, (float)w / (float)h, 0.1f, 150.0f); // Set the perspective projection
    glMatrixMode(GL_MODELVIEW); // Set the matrix mode back to modelview
}

// Main function
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // Set display mode with single buffer, RGB color, and depth buffer
    glutCreateWindow("Solar System"); // Create a window with the title "Solar System"
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering

    glutDisplayFunc(drawSolarSystem); // Set the display callback function
    glutReshapeFunc(reshape); // Set the reshape callback function
    glutTimerFunc(25, update, 0); // Set the timer callback function for animation updates

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set the clear color for the color buffer

    glutMainLoop(); // Enter the GLUT event processing loop

    return 0; // Return 0 to indicate successful completion
}
