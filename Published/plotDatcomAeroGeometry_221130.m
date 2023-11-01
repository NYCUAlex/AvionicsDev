%% Plot 2D aerodynamics geometry from Datcom input file
% Author: JW Huang
% Date: 2022/11/27

close all; clear;

shortDescription = 'Asfaloth(ver2)'; % latex format
inputFileName = 'Miss5.dat';

%% Init
% Variables
flagAXIBOD = 0; % Reading flag of AXIBOD
finNum = 0; % Number after $FINSET
finShape = zeros(100, 3);
finPhase = [];
X = [];
R = [];

% Constants
IndexXLE = 1;
IndexSSPAN = 2;
IndexCHORD = 3;
CONE = 0;
OGIVE = 1;
POWER = 2;
HAACK = 3;
KARMAN = 4;
BodyColor = [250 172 88]/255; % Light orange
FinColorList = [0.6 0.8 0.7 0.9 0.65 0.85 0.75]; % 7 types of gray

%% Read file
lines = readlines(inputFileName);
for i = 1:length(lines)
    ctext = lines(i);
    
    % Read Body, X-R type
    if contains(ctext, ' X=') || contains(ctext, ' X(')
        X = [X; splitStandardForm(ctext)];
    end
    if contains(ctext, ' R=') || contains(ctext, ' R(')
        R = [R; splitStandardForm(ctext)];
    end
    % Read Body, NOSE-CENTR-AFT type
    if contains(ctext, '$AXIBOD'), flagAXIBOD = 1; end
    if contains(ctext, ' TNOSE='),  tnose = splitStandardForm(ctext); end
    if contains(ctext, ' LNOSE='),  lnose = splitStandardForm(ctext); end
    if contains(ctext, ' DNOSE='),  dnose = splitStandardForm(ctext); end
    if contains(ctext, ' POWER='),  pnose = splitStandardForm(ctext); end
    if contains(ctext, ' LCENTR='), lbody = splitStandardForm(ctext); end
    if contains(ctext, ' DCENTR='), dbody = splitStandardForm(ctext); end
    if contains(ctext, ' TAFT='),   taft = splitStandardForm(ctext); end
    if contains(ctext, ' LAFT='),   laft = splitStandardForm(ctext); end
    if contains(ctext, ' DAFT='),   daft = splitStandardForm(ctext); end
    % Body data points for N-C-A type
    if contains(ctext, '$END') && flagAXIBOD == 1 && exist('lnose', 'var')
        flagAXIBOD = 0;
        % Default type
        if ~exist('tnose', 'var'), tnose = OGIVE; end
        if ~exist('taft', 'var'), taft = CONE; end
        % Nosecone part
        X = 0:lnose/50:lnose;
        X = X';
        switch tnose
            case CONE % Conical
                R = dnose/2 / lnose * X;
            case OGIVE % Tangent ogive
                rho = ((dnose/2)^2 + lnose^2) / dnose;
                r0 = sqrt(rho^2 - lnose^2);
                R = sqrt(rho^2 - (lnose-X).^2) - r0;
            case POWER % Power law
                R = dnose/2 * (X/lnose).^pnose;
            case HAACK % HAACK L-V (C=1/3)
                theta = acos(1-2*X/lnose);
                R = dnose/2/sqrt(pi) * ...
                    sqrt(theta - sin(2*theta)/2 + 1/3*(sin(theta)).^3);
            case KARMAN % KARMAN L-D (C=0)
                theta = acos(1-2*X/lnose);
                R = dnose/2/sqrt(pi) * ...
                    sqrt(theta - sin(2*theta)/2);
        end
        % Body part
        X = [X; X(end)+lbody];
        R = [R; dbody/2];
        % After part
        if exist('laft', 'var')
            Xaft = 0:laft/20:laft;
            r0 = (dbody - daft) / 2;
            switch taft
                case CONE % Conical
                    Raft = r0 - r0 * Xaft / laft + daft/2;
                case OGIVE % Tangent ogive
                    rho = (r0^2 + laft^2) / (r0*2);
                    r0 = sqrt(rho^2 - laft^2);
                    Raft = sqrt(rho^2 - Xaft.^2) - r0 + daft/2;
            end
            X = [X; Xaft(:)+max(X)];
            R = [R; Raft(:)];
        end
    end
    
    % Fin sets
    if contains(ctext, '$FINSET')
        temp = regexp(ctext,'\d*','Match');
        finNum = str2double(temp(1));
    end
    if contains(ctext, ' XLE=')
        temp = splitStandardForm(ctext);
        finShape(1:length(temp), IndexXLE, finNum) = temp;
    end
    if contains(ctext, ' SSPAN=')
        temp = splitStandardForm(ctext);
        finShape(1:length(temp), IndexSSPAN, finNum) = temp;
    end
    if contains(ctext, ' CHORD=')
        temp = splitStandardForm(ctext);
        finShape(1:length(temp), IndexCHORD, finNum) = temp;
    end
    if contains(ctext, ' PHIF=')
        finPhase(:, finNum) = NaN(10, 1);
        temp = splitStandardForm(ctext);
        finPhase(1:length(temp), finNum) = temp;
    end
end

%% Plot
fig = figure('units','normalized','outerposition',[0 0 1 1]);
% Body
X = [X; flip(X)];
R = [R; -flip(R)];
fillBody = fill(X, R, BodyColor);
fillBody.EdgeColor = BodyColor;
hold on;

% Fins
for i = 1:finNum
    cfin = finShape(:, :, i);
    cfin = cfin(cfin(:, IndexXLE)>0, :);
    finColor = [1 1 1] * FinColorList(rem(i, length(FinColorList)));
    % Fin data points
    x = [cfin(:, IndexXLE); flip(cfin(:, IndexXLE)+cfin(:, IndexCHORD))];
    r = [cfin(:, IndexSSPAN); flip(cfin(:, IndexSSPAN))];
    % Rotate and place
    for j = 1:length(finPhase)
        cphase = finPhase(j, i)-45;
        if cphase <= 180
            fill(x, r*cosd(cphase), finColor);
        end
    end
    % Text notes
    finSpan = max(r) - min(r);
    finQty = sum(~isnan(finPhase(:, i)));
    minPhase = min(finPhase(:, i));
    str = append('\leftarrow', ...
        '#', num2str(i), ...
        ' span ', num2str(max(r)-min(r)), 'cm', ...
        '\times', num2str(finQty), ' , ', ...
        num2str(minPhase), '^{\circ} ');
    indexArrow = size(cfin, 1) + 1;
    text(x(indexArrow), r(indexArrow)*cosd(minPhase), str,FontSize=15);
end

% Formats
alpha(0.8);
grid on;
% Plot limits
axis equal tight
xlim(xlim*1.1);
ylim(ylim*1.2);
% Title
xlabel("unit: cm");
title(shortDescription);

%% Save to files
filename = replaceSymbol(shortDescription);
copyfile(inputFileName, append(filename, '.dat'));
saveas(fig, append(filename, '.png'));

%% Sub-functions
function out = splitStandardForm(in)
    temp = split(in, '=');
    temp = split(temp(2), '    ');
    temp = str2double(split(temp(1), ','));
    out = temp(~isnan(temp));
end

function out = replaceSymbol(in)
    numIndex = in>=0x30 & in<=0x39;
    letterIndex = isletter(in);
    out = in;
    out(~(numIndex | letterIndex)) = '_';
end