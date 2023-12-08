# Differential Equations

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)

## This was done as homework for Differential Equations course at Innopolis University.

### Computational Practicum on 1st order ODE
Write a computer program in the C++ programming language that solves

<p align="center">
  <img src="./readme-files/task1.svg" alt="Equation 1" width="200px">
</p>
    on a given interval

<p align="center">
  <img src="./readme-files/task1_interval.svg" alt="Interval for equation 1" width="100px">
</p>

and provides the analysis of approximations.

<ol>
	<li>
		<p>Implement in the code the numerical Euler's method</p>
		<p align="center">
	  		<img src="./readme-files/task1_point_1.svg" alt="Task 1 Point 1" width="400px">
		</p>
	</li>
	<li>
		<p>Implement in the code the numerical Improved Euler's method</p>
		<p align="center">
			<img src="./readme-files/task1_point_2.svg" alt="Task 1 Point 2" width="400px">
		</p>
	</li>
	<li>
		<p>Implement in the code the numerical Runge-Kutta method</p>
		<p align="center">
			<img src="./readme-files/task1_point_3.svg" alt="Task 1 Point 3" width="400px">
		</p>
	</li>
	<li>
		<p>Hardcode the function of the right-hand side of the equation</p>
		<p align="center">
			<img src="./readme-files/task1_point_4_1.svg" alt="Task 1 Point 4_1" width="100px">
		</p>
		<p>as well as initial conditions</p>
		<p align="center">
			<img src="./readme-files/task1_point_4_2.svg" alt="Task 1 Point 4_2" width="100px">
		</p>
	</li>
	<li>
		<p>Solve the equation manually, hardcore the function of the analytical solution</p>
		<p align="center">
			<img src="./readme-files/task1_point_5.svg" alt="Task 1 Point 5" width="300px">
		</p>
	</li>
	<li>
		<p>For each numerical method compose the array of the local errors</p>
		<p align="center">
			<img src="./readme-files/task1_point_6.svg" alt="Task 1 Point 6" width="400px">
		</p>
		<p>given the number n of grid points</p>
	</li>
	<li>
		<p>For each numerical method compose the array of the global errors for each number n of grid points within the range</p>
		<p align="center">
			<img src="./readme-files/task1_point_7_1.svg" alt="Task 1 Point 4_1" width="200px">
		</p>
		<p align="center">
			<img src="./readme-files/task1_point_7_2.svg" alt="Task 1 Point 4_2" width="400px">
		</p>
	</li>
	<li>
		<p>Provide the functionality of printing the arrays onto the console in the format</p>
		<ul>
			<li>in the first line print the title of the array (e.g. "ti="),</li>
			<li>in the second line print the values stored in the array formatted "f5" (%.f5), separated by spaces, without the space after the last item, with the "\n" at the end of line. Note that decimal separator is dot(.).</li>
		</ul>
	</li>



</ol>

### Computational practicum on systems of 2 ODE

Write a computer program in the C++ programming language that solves

<p align="center">
  <img src="./readme-files/task2_1.svg" alt="Equation 2" width="200px">
</p>

<p align="center">
  <img src="./readme-files/task2_2.svg" alt="Equation 2 Interval" width="200px">
</p>

<ul>
	<li>
		<p>Implement Euler's method as described in tutorial</p>
	</li>
	
	<li>
		<p>Implement improved Euler's method  as described in tutorial</p>
	</li>
	
	<li>
		<p>Implement Runge-Kutta method analogically</p>
	</li>
	
	<li>
		<p>Hard code the functions f(x,y,t) and g(x,y,t) as well as the initial conditions t0, x0, y0</p>
	</li>
	
	<li>
		<p>Provide the functionality of printing the arrays onto the console as in the previous task</p>
	</li>

</ul>


