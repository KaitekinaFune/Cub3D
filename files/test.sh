make re
echo -e "\e[32mTesting \e[7m\e[1mnorth\e[0m"
./Cub3D maps/map_north.cub
echo -e "\e[32mTesting \e[7m\e[1meast\e[0m"
./Cub3D maps/map_east.cub
echo -e "\e[32mTesting \e[7m\e[1mwest\e[0m"
./Cub3D maps/map_west.cub
echo -e "\e[32mTesting \e[7m\e[1msouth\e[0m"
./Cub3D maps/map_south.cub
make clean