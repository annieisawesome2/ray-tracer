#include "tuple.h"
#include <iostream>
#include <cmath>

// Projectile structure
struct Projectile {
    Tuple position;
    Tuple velocity;
};

// Environment structure
struct Environment {
    Tuple gravity;
    Tuple wind;
};

// Tick function to update projectile position
Projectile tick(const Environment& env, const Projectile& proj) {
    Tuple position = add(proj.position, proj.velocity);
    Tuple velocity = add(add(proj.velocity, env.gravity), env.wind);
    return {position, velocity};
}

int main() {
    // Set up projectile
    Tuple start = point(0, 1, 0);
    Tuple velocity_vec = normalize(vector(1, 1.8, 0));
    multiply(velocity_vec, 11.25); // increase magnitude
    Projectile p = {start, velocity_vec};
    
    // Set up environment
    Tuple gravity = vector(0, -0.1, 0);
    Tuple wind = vector(-0.01, 0, 0);
    Environment e = {gravity, wind};
    
    // Create canvas
    Canvas c = canvas(900, 550);
    Color projectile_color = color(1, 0, 0); // Red
    
    // Simulate projectile trajectory
    int tick_count = 0;
    while (p.position.y > 0) {
        // Convert world coordinates to canvas coordinates
        // Canvas y is upside-down, so subtract from height
        int canvas_x = static_cast<int>(std::round(p.position.x));
        int canvas_y = c.height - static_cast<int>(std::round(p.position.y));
        
        // Only plot if within canvas bounds
        if (canvas_x >= 0 && canvas_x < c.width && canvas_y >= 0 && canvas_y < c.height) {
            write_pixel(c, canvas_x, canvas_y, projectile_color);
        }
        
        // Update projectile
        p = tick(e, p);
        tick_count++;
        
        // Safety check to prevent infinite loop
        if (tick_count > 10000) {
            std::cout << "Warning: Projectile simulation exceeded 10000 ticks" << std::endl;
            break;
        }
    }
    
    std::cout << "Projectile simulation completed in " << tick_count << " ticks" << std::endl;
    std::cout << "Final position: (" << p.position.x << ", " << p.position.y << ", " << p.position.z << ")" << std::endl;
    
    // Save canvas to file
    save_canvas_to_file(c, "projectile.ppm");
    std::cout << "Canvas saved to projectile.ppm" << std::endl;
    std::cout << "To view on Mac, run: open projectile.ppm" << std::endl;
    
    return 0;
}

