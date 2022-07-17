# Shipping Company 

## Summary 
This project was done as a part of our Data structure and algorithms course, the project itself is a simulation of a shipping company full with trucks and maintenance and delivery and roads. it's a detailed log of a operation that these companies do hour by hour, it's the project is systems and rules to get good use of the trucks and to get the delivery to the customer as efficiently as possible.  
The Initial state of the company is depended on the input file.  

## Trucks 
there are 3 types of trucks Normal, Special, Vip each truck is responsible for their respective cargos.  
for each truck the following info is available :
-  ID : A unique token for each truck given in the initial state.
-  Speed : the speed of the truck km/h.
-  Capacity : the total amount of cargo that can be loaded on the truck.
-  Active Time : is used for maintaining the truck.
-  Delivery Interval : the need for the truck to go from the company to the customer.
### Normal Trucks 
Normal trucks can load Normal Cargo and Vip Cargo with the priority to the vip Cargo they generally have large capacities and they're generally slower than the other types of trucks.
### Special Trucks 
Special trucks can only load Special Cargo. 
### Vip Trucks 
Vip trucks can load Vip Cargo and Normal Cargo with the priority to the vip Cargo, they generally have small capacities and they're generally faster than the other types of trucks. 

## Events 
there are 3 types of Events in this simulation
- Ready Event : Initializes a new Cargo and provides the following information the Cargo type, the event time, the ID of the Cargo, the distance, Loading Time and the cost. 
- Cancellation Events : Cancels the order if the it hasn't been loaded yet providing the event time and the ID of the Cargo that has to be canceled.  
- Promotion Event : promote a normal cargo to become a Vip Cargo, providing the event time, the ID of the Cargo, and the extra money for the promotion. 