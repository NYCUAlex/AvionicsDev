clearvars;
close all;
% Add path to stlTools
% You can download the package for free from: 
% https://es.mathworks.com/matlabcentral/fileexchange/51200-stltools
addpath('.\stlTools\');
% Set the name of the mat file containing all the info of the 3D model
MatFileName = 'rocket_model.mat';
% Define the list of parts which will be part of the rigid aircraft body
rigid_body_list   = {'Payload.stl','Forward Section.stl','Propulsion.stl'};
% Define the color of each part
rigid_body_colors = {0.0 * [1, 1, 1],0.3 * [1, 1, 1],0.5 * [1, 1, 1]};
% Define the transparency of each part
alphas            = [1,1,1];
% Define the model ofset to center the A/C Center of Gravity
offset_3d_model   = 1 * [3.0, 0, 0];

% Construct the main body
for i = 1:length(rigid_body_list)
    Model3D.Aircraft(i).model = rigid_body_list{i};
    Model3D.Aircraft(i).color = rigid_body_colors{i};
    Model3D.Aircraft(i).alpha = alphas(i);
    % Read the *.stl file
   [Model3D.Aircraft(i).stl_data.vertices, Model3D.Aircraft(i).stl_data.faces, ~, ~] = stlRead(rigid_body_list{i});
%     y = Model3D.Aircraft(i).stl_data.vertices(:, 2);
%     z = Model3D.Aircraft(i).stl_data.vertices(:, 3);
%     Model3D.Aircraft(i).stl_data.vertices(:, 2) = -z;
%     Model3D.Aircraft(i).stl_data.vertices(:, 3) =  y;
%     Model3D.Aircraft(i).stl_data.vertices  = Model3D.Aircraft(i).stl_data.vertices - offset_3d_model;
end



% Define the controls 
ControlsFieldNames = {...
'model'  'label' 'color' 'rot_offset_deg' 'rot_point'  'rot_vect' 'max_deflection'};
Controls = {
'Canard_1.stl', 'CAN_1', 0.5*[1, 1, 1], 0, [1.5, 0, 0], [0,  1, 0], [-10, +10];
'Canard_2.stl', 'CAN_2', 0.5*[1, 1, 1], 0, [1.5, 0, 0], [1,  0, 0], [-10, +10];
'Canard_3.stl', 'CAN_3', 0.5*[1, 1, 1], 0, [1.5, 0, 0], [0, -1, 0], [-10, +10];
'Canard_4.stl', 'CAN_4', 0.5*[1, 1, 1], 0, [1.5, 0, 0], [-1, 0, 0], [-10, +10]};

for i = 1:size(Controls, 1)
    for j = 1:size(Controls, 2)
        Model3D.Control(i).(ControlsFieldNames{j}) = Controls{i, j};
    end
    % Read the *.stl file
    [Model3D.Control(i).stl_data.vertices, Model3D.Control(i).stl_data.faces, ~, ~] = stlRead( Model3D.Control(i).model);
%     y = Model3D.Control(i).stl_data.vertices(:, 2);
%     z = Model3D.Control(i).stl_data.vertices(:, 3);
%     Model3D.Control(i).stl_data.vertices(:, 2) = -z;
%     Model3D.Control(i).stl_data.vertices(:, 3) =  y;
%     Model3D.Control(i).stl_data.vertices = Model3D.Control(i).stl_data.vertices - offset_3d_model;
    
end

%% Save mat file
save(MatFileName, 'Model3D');

%% Check the results
plot3Dmodel(MatFileName)