# Billiards
## How is math used in billiards programming?

Billiards game is a game that uses geometric math a lot, and I made this game for the purpose of learning, studying, and improving my geometric math.

In this game, the most used are trigonometric formulas which the students think they are useless.

To make this game I use vectors and some math formulas (trigonometric formulas).

### What are vectors used for?
- They are used to determine an object's position, or velocity.

### What are trigonometric formulas used for?
- They are used for the purpose of calculating the angle of an object

## How i used them

- For example, we have mouse position (x<sub>2</sub>: 1007; y<sub>2</sub>: 12) and ball position (x<sub>1</sub>: 400; y<sub>1</sub>: 290)

![](https://media.discordapp.net/attachments/636515552428425236/900312017666207754/image0.jpg?width=705&height=375)

How do we calculate the angle of the stick?

1. First we need to calculate the opposite:

   ![](https://bit.ly/3jlp6sN)

2. Next, we need to calculate the hypotenuse:

   ![](http://www.sciweavers.org/tex2img.php?eq=%20%5Csqrt%7B%28x_2%20-%20x_1%29%5E2%20%2B%20%28y_2%20-%20y_1%29%5E2%7D%20%3D%20%20%5Csqrt%7B%281107%20-%20400%29%5E2%20%2B%20%2812%20-%20290%29%5E2%7D%20%20%5Capprox%20759.693&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0)

3. After calculate the opposite and hypotenuse then we calculate the angle of the stick (use inverse sine):

   ![](https://bit.ly/3C11X62)
   
4. We need to check if x<sub>1</sub> > x<sub>2</sub> then angle = 180° - angle.
5. If the angle < 0 then the angle will add 360°

Finally the angle of the stick is 158.524°

Full of the code
```cpp
double opposite = vector2.getY() - vector.getY();
double hypotenuse = std::hypot(vector2.getX() - vector.getX(), vector2.getY() - vector.getY());

double degrees = (std::asin(opposite / hypotenuse) * 180) / PI + 180;

if (vector.getX() > vector2.getX()) degrees = 180 - degrees;
if (degrees < 0) degrees += 360;

return degrees;
```

And when you click on the screen, the stick will automatically move back, to do that we need do:
1. Calculate the angle of the mouse:
  
  - Opposite:
    ![](https://bit.ly/3jlp6sN)
  - Adjacent:
    ![](https://bit.ly/3jDiZAj)
  
  - Use atan2:
    ![](https://bit.ly/2Z3QIvD)
    
2. Change the position of the stick:
  - stick's x add 5 * cos(-0.37463)
  - sticks's y add 5 * sin(-0.37463)
