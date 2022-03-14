fid = fopen('Chevauchement.txt');
n0 = textscan(fid,'%d',1); %lecture du nombre d'obstacles
n = n0{1,1};

j=1;

while(j~=n+1)
    m0 = textscan(fid,'%d',1); %lecture du nombre de segments dans le premier obstacle
    m_i = m0{1,1};
    obstacle = zeros(m_i,4); % matrice des coordonnées des points des segments de l'obstacle i
    for i=1:m_i
        k = textscan(fid,'%f',1);
        obstacle(i,1) = k{1,1};
        k = textscan(fid,'%f',1);
        obstacle(i,2) = k{1,1};
        k = textscan(fid,'%f',1);
        obstacle(i,3) = k{1,1};
        k = textscan(fid,'%f',1);
        obstacle(i,4) = k{1,1};
    end
    hold on
    col = rand(1,3);% fixer une couleur
    for i=1:m_i
    plot([obstacle(i,1) obstacle(i,3)],[obstacle(i,2) obstacle(i,4)], 'Color',col);
    end
    j=j+1;
end
hold off


% ZZ = 1:5;
% for k = 1:10
%   dTdz3 = rand(1,5);
%   plot(ZZ,dTdz3, 'Color', rand(1,3))
%   hold on;
% end



