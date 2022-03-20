fid = fopen('trajectoire.txt');
p0 = textscan(fid,'%d',1); %lecture du nombre de segments valides qui forment les obstacles
p = p0{1,1};
n0 = textscan(fid,'%d',1); %lecture du nombre d'obstacles
n = n0{1,1};




obstacle = zeros(p,4); % matrice des coordonnées des points des segments valides qui forment les obstacles
i=1;

while(i~=p+1)
    k = textscan(fid,'%f',1);
    obstacle(i,1) = k{1,1};
    k = textscan(fid,'%f',1);
    obstacle(i,2) = k{1,1};
    k = textscan(fid,'%f',1);
    obstacle(i,3) = k{1,1};
    k = textscan(fid,'%f',1);
    obstacle(i,4) = k{1,1};
    i=i+1;
end
hold on
for i=1:(p)
    plot([obstacle(i,1) obstacle(i,3)],[obstacle(i,2) obstacle(i,4)], 'Color', 'blue');
end



q0 = textscan(fid,'%d',1); %lecture du nombre de points constituant la trajectoire finale
q = q0{1,1};


trajectoire = zeros(q,2);
i=1;

while(i~=q+1)
    k = textscan(fid,'%f',1);
    trajectoire(i,1) = k{1,1};
    k = textscan(fid,'%f',1);
    trajectoire(i,2) = k{1,1};
    i=i+1;
end

for i=1:(q-1)
    plot([trajectoire(i,1) trajectoire(i+1,1)],[trajectoire(i,2) trajectoire(i+1,2)],'Color','red');
end
hold off

title('Trajectoire optimale')


fclose(fid);

























