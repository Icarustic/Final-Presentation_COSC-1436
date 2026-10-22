## Final Presentation Project: PID System for a Simulated Drone.
---
### Overview:
- What is a PID System?
- ***PID System***: Tries to correct the difference between the current value and the desired value using a formula. In the case of drones, this helps maintain their orientation.
-  Structured by `Error = Setpoint - Measurement or Change = DesiredPosition - CurrentPosition.`
> Formula: `Total Correction = (Proportional_Intensity * Error) + (Integral_Intensity * Sum {Error * Time}) + (Derivative_Intensity * ((CurrentError - LastError) / Time))`
>> Description: Amount of Error to fix + Error amount times how long it has happened (helps correct persistent error over time) + All Changes in Error divided by the time they occur (this smooths the change between the corrections to make it more gradually transition between states/positions) (Helps remove oscillation since the program doesn't overshoot the setpoint.)
---
### Implementation
- ***PID Systems***: Each regulated value requires its own PID system to manage.
  
<img width="1526" height="327" alt="image" src="https://github.com/user-attachments/assets/21cc8244-719a-4c37-b670-9602d17fb148" />

- Note: Traditional Drones turn using CW and CCW spinning propellers, 2 for each diagonal, where CCW speeds up and CW slows down, causing a turn.

---
- ***Translation/Communication***: How does the drone communicate its orientation with the program/computer?
> 1. Gimbal Sensor & Speedometer & Compact Bearing/Propeller Gear Drive
> 2. Gimbal Sensor & Propeller Gear Drive
> 3. Compass Sensor Add-on & External Rotation Source
> 4. Altitude Sensor & Rotational Speed Controller
- ***Caveats***: Special considerations for the project.
> - Redstone has a maximum range of 0-15; therefore, when communicating numerical values, they must be translated to be accurately represented in-game.
> - Simplified Physics works both to the benefit and detriment of the drone.
> - Create a C++ program, then port it into Lua Scripts.

---
### Components List:
> 1. Gimbal Sensor x1 (general)
> 2. Altitude Sensor x1 (general)
> 3. Speedometer x1
> 4. Rotational Speed Controller x2 (+1) (propellor speed & direction)
> 5. RedRouter x1 (Redstone links x4) (propeller arm tilt)
---
### Design
<img width="762" height="571" alt="Screenshot 2026-10-17 050622" src="https://github.com/user-attachments/assets/e6c86159-d312-44c8-94a0-0ecf4f0915eb" />
<img width="763" height="572" alt="Screenshot 2026-10-17 051956" src="https://github.com/user-attachments/assets/1855576b-9ae5-43d0-9aed-f2b4d336ef92" />
<img width="787" height="478" alt="Screenshot 2026-10-17 050910" src="https://github.com/user-attachments/assets/5ae0c078-5585-4822-a4f4-27c8ab8195d1" />









