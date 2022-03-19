fid = fopen('Normale.txt');
n0 = textscan(fid,'%d',1); %lecture du nombre de points
n = n0{1,1};

obstacle = zeros(n,4); % matrice des coordonnées des points des segments 
j=1;


while(j~=n+1) 
    for i=1:n
        k = textscan(fid,'%f',1);
        obstacle(i,1) = k{1,1};
        k = textscan(fid,'%f',1);
        obstacle(i,2) = k{1,1};
        k = textscan(fid,'%f',1);
        obstacle(i,3) = k{1,1};
        k = textscan(fid,'%f',1);
        obstacle(i,4) = k{1,1};
        j=j+1;
    end
end

hold on
for i=1:n
    plot([obstacle(i,1) obstacle(i,3)],[obstacle(i,2) obstacle(i,4)], 'Color', 'blue');
end

m0 = textscan(fid,'%d',1); %lecture du nombre de normales
m = m0{1,1};

normales = zeros(m,2); % matrice des coordonnées des points des segments 
i=1; 
while(i~=(m+1))
    k = textscan(fid,'%f',1);
    normales(i,1) = k{1,1};
    k = textscan(fid,'%f',1);
    normales(i,2) = k{1,1};
    k = textscan(fid,'%f',1);
    normales(i+1,1) = k{1,1};
    k = textscan(fid,'%f',1);
    normales(i+1,2) = k{1,1};
    i=i+2;
end

i=1; 
while(i~=(m+1))
    plot([normales(i,1),normales(i+1,1)],[normales(i,2),normales(i+1,2)], 'Color', 'green');
    i=i+2;
end
hold off;

fclose(fid);


