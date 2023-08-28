#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#include "rtweekend.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "moving_sphere.h"
#include "aarect.h"
#include "box.h"

int cnt=1;
hittable_list random_scene()
{
    hittable_list world;

    //auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    //world.add(make_shared<sphere>(point3(0,-500,0), 500, ground_material));
    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
    world.add(make_shared<sphere>(point3(0,-500,0), 500, make_shared<lambertian>(checker)));

    for (int a = 0; a < 10; a++)
    {
        for (int b = 0; b < 10; b++)
        {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9)
            {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8)
                {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center + vec3(0, random_double(0,.5), 0);
                    world.add(make_shared<moving_sphere>(
                                  center, center2, 0.0, 1.0, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95)
                {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else
                {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}

hittable_list simple_light()
{
    hittable_list objects;

    auto pertext = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    objects.add(make_shared<sphere>(point3(0,-500,0), 500, pertext));
    objects.add(make_shared<sphere>(point3(0,2,0), 2, pertext));

    auto difflight = make_shared<diffuse_light>(color(4,4,4));
    objects.add(make_shared<xy_rect>(1, 7, 1, 5, -2, difflight));

    return objects;
}

hittable_list cornell_box()
{
    hittable_list objects;

    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    //auto gray = make_shared<lambertian>(color(.1, .1, .1));
    auto gray=make_shared<lambertian>(color(0.5,0.5,0.5));
    //objects.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
    //objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, white));
    //objects.add(make_shared<xz_rect>(150, 450, 150, 450, 554, light));
    //objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
    //objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
    //objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));

    /*shared_ptr<hittable> box1 = make_shared<box>(point3(0, 0, 0), point3(165, 330, 165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265,0,295));
    objects.add(box1);

    shared_ptr<hittable> box2 = make_shared<box>(point3(0,0,0), point3(165,165,165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, vec3(130,0,65));
    objects.add(box2);*/

    //auto glossy1 = make_shared<metal>(vec3(1, 1, 1), 0.05);
    auto glossy1 = make_shared<metal_ggx>(vec3(1, 1, 1), 0.05);
    shared_ptr<hittable> board1 = make_shared<box>(point3(0, 0, 0), point3(10, 555, 75), glossy1);
	board1 = make_shared<rotate_y>(board1, 62);//62//57
	board1 = make_shared<translate>(board1, vec3(275, 0, 350));
	objects.add(board1);

	auto glossy2 = make_shared<metal_ggx>(vec3(1, 1, 1), 0.10);
	shared_ptr<hittable> board2 = make_shared<box>(point3(0, 0, 0), point3(10, 555, 75), glossy2);
	board2 = make_shared<rotate_y>(board2, 46);//42//40
	board2 = make_shared<translate>(board2, vec3(200, 0, 300));
	objects.add(board2);

	auto glossy3 = make_shared<metal_ggx>(vec3(1, 1, 1), 0.15);
	shared_ptr<hittable> board3 = make_shared<box>(point3(0, 0, 0), point3(10, 555, 75), glossy3);
	board3 = make_shared<rotate_y>(board3, 38);//32//33
	board3 = make_shared<translate>(board3, vec3(125, 0, 250));
	objects.add(board3);

	auto glossy4 = make_shared<metal_ggx>(vec3(1, 1, 1), 0.20);
	shared_ptr<hittable> board4 = make_shared<box>(point3(0, 0, 0), point3(10, 555, 75), glossy4);
	board4 = make_shared<rotate_y>(board4, 32);//23//27//24
	board4 = make_shared<translate>(board4, vec3(50, 0, 175));
	objects.add(board4);

    auto light1 = make_shared<diffuse_light>(color(8, 8, 8));
    auto light2 = make_shared<diffuse_light>(color(4, 4, 4));
	auto light3 = make_shared<diffuse_light>(color(2, 2, 2));
	auto light4 = make_shared<diffuse_light>(color(1, 1, 1));

	objects.add(make_shared<sphere>(point3(400, 111, 300), 5,  light1));
	objects.add(make_shared<sphere>(point3(400, 230, 300), 10, light2));
	objects.add(make_shared<sphere>(point3(400, 333, 300), 20, light3));
	objects.add(make_shared<sphere>(point3(400, 470, 300), 40, light4));


	//objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, gray));
	//objects.add(make_shared<flip_face>(make_shared<xy_rect>(0, 555, 0, 555, 555, gray)));

    return objects;
}

hittable_list veach_mis() {
	hittable_list objects;

	auto gray = make_shared<lambertian>(color(.1, .1, .1));
	auto glossy1 = make_shared<metal>(vec3(1, 1, 1), 0.05);
	auto glossy2 = make_shared<metal>(vec3(1, 1, 1), 0.10);
	auto glossy3 = make_shared<metal>(vec3(1, 1, 1), 0.15);
	auto glossy4 = make_shared<lambertian>(vec3(1, 0, 0));
	auto light1 = make_shared<diffuse_light>(color(8, 8, 8));
	auto light2 = make_shared<diffuse_light>(color(4, 4, 4));
	auto light3 = make_shared<diffuse_light>(color(2, 2, 2));
	auto light4 = make_shared<diffuse_light>(color(1, 1, 1));
	auto walllight = make_shared<diffuse_light>(color(7, 7, 7));

	//sphere light
	objects.add(make_shared<sphere>(point3(400, 111, 300), 5,  light1));
	objects.add(make_shared<sphere>(point3(400, 230, 300), 10, light2));
	objects.add(make_shared<sphere>(point3(400, 333, 300), 20, light3));
	objects.add(make_shared<sphere>(point3(400, 444, 300), 40, light4));

	//board
	/*
	//shared_ptr<hittable> board1 = make_shared<box>(point3(0,250,500), point3(555,260,525), black);
	//board1 = make_shared<rotate_y>(board1, 40);
	//objects.add(board1);
	//shared_ptr<hittable> board2 = make_shared<box>(point3(0, 200, 450), point3(555, 210, 475), black);
	//board2 = make_shared<rotate_y>(board2, 30);
	//objects.add(board2);
	//shared_ptr<hittable> board3 = make_shared<box>(point3(0, 150, 400), point3(555, 160, 425), black);
	//board3 = make_shared<rotate_y>(board3, 20);
	//objects.add(board3);
	//shared_ptr<hittable> board4 = make_shared<box>(point3(0, 100, 350), point3(555, 110, 375), black);
	//board4 = make_shared<rotate_y>(board4, 10);
	//objects.add(board4);
	*/

	//objects.add(make_shared<flip_face>(make_shared<yz_rect>(0, 555, 0, 555, 555, gray)));//left
	//objects.add(make_shared<flip_face>(make_shared<yz_rect>(0, 555, 0, 555, 555, walllight)));//light
	objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, gray)); //right
	//objects.add(make_shared<flip_face>(make_shared<xz_rect>(0, 555, 0, 555, 555, gray)));//ceiling
	//objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, gray));//floor
	objects.add(make_shared<flip_face>(make_shared<xy_rect>(0, 555, 0, 555, 555, gray)));//back

	//shared_ptr<hittable> board1 = make_shared<box>(point3(250, 0, 350), point3(255, 555, 375), gray);
	shared_ptr<hittable> board1 = make_shared<box>(point3(0, 0, 0), point3(5, 555, 50), glossy1);
	board1 = make_shared<rotate_y>(board1, 57);//62//57
	board1 = make_shared<translate>(board1, vec3(275, 0, 350));
	objects.add(board1);
	//shared_ptr<hittable> board2 = make_shared<box>(point3(200, 0, 300), point3(205, 555, 325), gray);
	shared_ptr<hittable> board2 = make_shared<box>(point3(0, 0, 0), point3(5, 555, 50), glossy2);
	board2 = make_shared<rotate_y>(board2, 41);//42//40
	board2 = make_shared<translate>(board2, vec3(200, 0, 300));
	objects.add(board2);
	//shared_ptr<hittable> board3 = make_shared<box>(point3(150, 0, 250), point3(155, 555, 275), gray);
	shared_ptr<hittable> board3 = make_shared<box>(point3(0, 0, 0), point3(5, 555, 50), glossy3);
	board3 = make_shared<rotate_y>(board3, 33);//32//33
	board3 = make_shared<translate>(board3, vec3(125, 0, 250));
	objects.add(board3);
	//shared_ptr<hittable> board4 = make_shared<box>(point3(100, 0, 200), point3(105, 555, 225), gray);
	shared_ptr<hittable> board4 = make_shared<box>(point3(0, 0, 0), point3(5, 555, 50), glossy4);
	board4 = make_shared<rotate_y>(board4, 24.5);//23//27//24
	board4 = make_shared<translate>(board4, vec3(50, 0, 175));
	objects.add(board4);

	//path notation
	//point3 lookfrom(180, 400, -800);
	//point3 lookat(278, 278, 0);

	//origin
	//point3 lookfrom(278, 278, -800);
	//point3 lookat(278, 278, 0);

	//veach
	/*point3 lookfrom(450, 278, -700);
	point3 lookat(275, 278, 0);

	auto vfov = 45.0;
	//vec3 vup(0, 1, 0);
	vec3 vup(1, 0, 0);
	auto aperture = 0.0;
	auto dist_to_focus = 10.0;
	auto t0 = 0.0;
	auto t1 = 1.0;

	cam = camera(lookfrom, lookat, vup, vfov, aspect, aperture, dist_to_focus, t0, t1);*/

	return objects;
}
color ray_color(const ray& r, const color& background, const hittable& world, shared_ptr<hittable> lights, int depth)
{
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth < 0)
        return color(0,0,0);


    // If the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, infinity, rec))
        return background;
scatter_record srec;
    color emitted = rec.mat_ptr->emitted(r, rec, rec.u, rec.v, rec.p);
    if (!rec.mat_ptr->scatter(r, rec, srec))
        return emitted;


    if (srec.is_specular) {
        return srec.attenuation
             * ray_color(srec.specular_ray, background, world, lights, depth-1);
    }


    auto light_ptr = make_shared<hittable_pdf>(lights, rec.p);
    mixture_pdf p(light_ptr, srec.pdf_ptr);

    ray scattered = ray(rec.p, p.generate(), r.time());
    auto pdf_val = p.value(scattered.direction());

    if(pdf_val <= 0) return color(0,0,0);

    return emitted
        + srec.attenuation * rec.mat_ptr->scattering_pdf(r, rec, scattered)
                           * ray_color(scattered, background, world, lights, depth-1) / pdf_val;
    /*ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

    double pdf;
    double pdf_val;
    color albedo;

    if (!rec.mat_ptr->scatter(r, rec, albedo, scattered, pdf))
        return emitted;

    hittable_pdf light_pdf(lights, rec.p);
    scattered = ray(rec.p, light_pdf.generate(), r.time());
    pdf_val = light_pdf.value(scattered.direction());
*/
    /*auto on_light = point3(random_double(213,343), 554, random_double(227,332));
    auto to_light = on_light - rec.p;
    auto distance_squared = to_light.length_squared();
    to_light = unit_vector(to_light);

    if (dot(to_light, rec.normal) < 0)
        return emitted;

    double light_area = (343-213)*(332-227);
    auto light_cosine = fabs(to_light.y());
    if (light_cosine < 0.000001)
        return emitted;

    pdf = distance_squared / (light_cosine * light_area);
    scattered = ray(rec.p, to_light, r.time());
*/

    /*return emitted
         + albedo * rec.mat_ptr->scattering_pdf(r, rec, scattered)
                  * ray_color(scattered, background, world, depth-1) / pdf;
                  */
    /*return emitted
         + albedo * rec.mat_ptr->scattering_pdf(r, rec, scattered)
                  * ray_color(scattered, background, world, lights, depth-1) / pdf_val;*/
    /*if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;

    return emitted + attenuation * ray_color(scattered, background, world, depth-1);*/

    /*if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }*/
    /*
    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            point3 light=vec3(5,10,0);
            ray lightdir;
            lightdir.orig=scattered.orig;
            lightdir.dir=light-scattered.origin();
            if(world.hit(lightdir,0.001,lightdir.direction().length()-0.001,rec))
            {
                //std::cerr<<lightdir.direction()<<std::flush;
                return color(0,0,0);
            }
            return attenuation * ray_color(scattered, world, depth-1);
        }

        //return color(0,0,0);
    }*/


    /*vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);*/
}

int main()
{

    // Image
    const auto aspect_ratio = 1.0;
    const int image_width = 512;
    //const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 5;
    const int max_depth = 10;

    point3 lookfrom(26,3,6);
    point3 lookat(0,2,0);
    vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;
    auto vfov = 40.0;
    color background(0,0,0);
    // World
    auto world=random_scene();

    //auto world=simple_light();
    switch (0)
    {
    case 1:
        world = random_scene();
        background = color(0.70, 0.80, 1.00);
        lookfrom = point3(13,2,3);
        lookat = point3(0,0,0);
        vfov = 20.0;
        aperture = 0.1;
        break;

    case 2:

        break;

    case 3:

        break;
    case 4:

        break;

    case 5:
        world = simple_light();
        //samples_per_pixel = 400;
        background = color(0,0,0);
        lookfrom = point3(26,3,6);
        lookat = point3(0,2,0);
        vfov = 20.0;
        break;

default:
    case 6:
        world = cornell_box();
        //aspect_ratio = 1.0;
        //image_width = 600;
        //samples_per_pixel = 200;
        background = color(0,0,0);
        lookfrom = point3(278, 278, -800);
        lookat = point3(278, 278, 0);
        vfov = 40.0;
        vup=point3(1,0,0);
        break;

    case 7:
        world=veach_mis();
        background = color(0,0,0);
        point3 lookfrom(450, 278, -700);
	    point3 lookat(275, 278, 0);
	    vfov = 40.0;
	    vup=point3(1,0,0);
	    break;
    }
    auto lights = make_shared<hittable_list>();
    lights->add(make_shared<sphere>(point3(400, 111, 300), 5, shared_ptr<material>()));
	lights->add(make_shared<sphere>(point3(400, 230, 300), 10, shared_ptr<material>()));
	lights->add(make_shared<sphere>(point3(400, 333, 300), 20, shared_ptr<material>()));
	lights->add(make_shared<sphere>(point3(400, 470, 300), 40, shared_ptr<material>()));
    /*auto R = cos(pi/4);
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_left = make_shared<lambertian>(color(0.9, 0.2, 0.3));
    auto material_center   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color(0.9, 0.9, 0.9));

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( -1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3(0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3(0.0,    0.0, -1.0), -0.45, material_center));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
    */
    // Camera

    //camera cam(point3(0,0,1), point3(0,0,-1), vec3(0,1,0), 45, aspect_ratio);

    //background = color(0.70, 0.80, 1.00);
    int image_height = static_cast<int>(image_width / aspect_ratio);


    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    clock_t start, end; // 儲存時間用的變數
    start = clock(); // 計算開始時間
    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                //pixel_color += ray_color(r, world, max_depth);
                pixel_color += ray_color(r, background, world, lights, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    end = clock(); // 計算結束時間
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // 計算
    std ::cerr<<"\n"<<cpu_time_used<<"\n";
    std::cerr << "\nDone.\n";

}
