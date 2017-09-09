# FinalProject-EE96: Intel Edison Physical Therapy Motion Classification
EE96C (Intel Edison, IOT Course)
----
Intel Edison basics, HTTP protocol, SSH, mounting on Grove Shield for GPIO, setting up basic client server interactions, etc
Final Project focused on machine learning and using 9 DOF (Degrees of Freedom) sensor, with FANN (Fast artificial neural network) API to classify 3 types of motions. Link to project can be found in my personal website, or here
The basic idea is our team wanted to utilize the FANN API to incorporate machine learning with data that can be collected using the 9 DOF
sensor's accelerometer and gyroscope, recording values from the x y z coordinates for the best classification of a correct bicep curl, shoulder press,
and random motion. AFter collecting the data, we trained the neural network with prior data to differentiate 3 separate motions, and used the intel edison as 
the main processor after mounting the 9 DOF block. In practical uses, this can be hooked up either in serial connection or preferrably, SSH
to a monitor and run the test neural network program in a c shell. After performing a motion, the program will generate a text that 
identifies the motion based on how the network was trained. It was pretty accurate in our demo. Link to project powerpoint here or above:
https://docs.google.com/presentation/d/1pQcIurjjxO_pS6xbqxPL35JCNGeh78hGp8_CLQC_na0/edit
Link to video demo:
https://www.youtube.com/watch?v=vbDzIktZ6Go&index=6&list=PLWMfJ0QmZ0FXYXG3_rYL_88Evo2KLB2Ty
