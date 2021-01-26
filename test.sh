make re

echo -e "\e[1mTesting good maps: \e[0m"
echo -e  "./Cub3D maps/map_valid_no_space.cub"
./Cub3D maps/map_valid_no_space.cub
echo -e "./Cub3D maps/map_valid_with_spaces.cub"
./Cub3D maps/map_valid_with_spaces.cub

echo -e "\e[1mTesting bad maps: \e[0m"
echo -e "\e[1mMissing specifications: \e[0m"
./Cub3D maps/map_bad_no_no.cub
./Cub3D maps/map_bad_no_so.cub
./Cub3D maps/map_bad_no_ea.cub
./Cub3D maps/map_bad_no_we.cub
./Cub3D maps/map_bad_no_s.cub
echo -e ""
echo -e ""
echo -e "\e[1mBad colors:\e[0m"
./Cub3D maps/map_bad_f_color.cub
./Cub3D maps/map_bad_c_color.cub
echo -e ""
echo -e ""
echo -e "\e[1mMissing line:\e[0m"
./Cub3D maps/map_bad_empty_spec.cub
echo -e ""
echo -e ""
echo -e "\e[1mDouble lines:\e[0m"
./Cub3D maps/map_bad_double.cub
echo -e ""
echo -e ""
echo -e "\e[1mEmpty line:\e[0m"
./Cub3D maps/map_bad_empty.cub
echo -e ""
echo -e ""
echo -e "\e[1mEmpty line in map:\e[0m"
./Cub3D maps/map_bad_hole.cub
echo -e ""
echo -e ""
echo -e "\e[1mMissing textures: \e[0m"
./Cub3D maps/map_bad_text_path0.cub
./Cub3D maps/map_bad_text_path1.cub
./Cub3D maps/map_bad_text_path2.cub
./Cub3D maps/map_bad_text_path3.cub
./Cub3D maps/map_bad_text_path4.cub
