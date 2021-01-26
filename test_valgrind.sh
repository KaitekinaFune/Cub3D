make re

echo -e "\e[1mTesting good maps: \e[0m"
echo -e  "valgrind ./Cub3D maps/map_valid_no_space.cub"
valgrind ./Cub3D maps/map_valid_no_space.cub
echo -e "valgrind ./Cub3D maps/map_valid_with_spaces.cub"
valgrind ./Cub3D maps/map_valid_with_spaces.cub

echo -e "\e[1mTesting bad maps: \e[0m"
echo -e "\e[1mMissing specifications: \e[0m"
valgrind ./Cub3D maps/map_bad_no_no.cub
valgrind ./Cub3D maps/map_bad_no_so.cub
valgrind ./Cub3D maps/map_bad_no_ea.cub
valgrind ./Cub3D maps/map_bad_no_we.cub
valgrind ./Cub3D maps/map_bad_no_s.cub
echo -e ""
echo -e ""
echo -e "\e[1mBad colors:\e[0m"
valgrind ./Cub3D maps/map_bad_f_color.cub
valgrind ./Cub3D maps/map_bad_c_color.cub
echo -e ""
echo -e ""
echo -e "\e[1mMissing line:\e[0m"
valgrind ./Cub3D maps/map_bad_empty_spec.cub
echo -e ""
echo -e ""
echo -e "\e[1mDouble lines:\e[0m"
valgrind ./Cub3D maps/map_bad_double.cub
echo -e ""
echo -e ""
echo -e "\e[1mEmpty line:\e[0m"
valgrind ./Cub3D maps/map_bad_empty.cub
echo -e ""
echo -e ""
echo -e "\e[1mEmpty line in map:\e[0m"
valgrind ./Cub3D maps/map_bad_hole.cub
echo -e ""
echo -e ""
echo -e "\e[1mMissing textures: \e[0m"
valgrind ./Cub3D maps/map_bad_text_path0.cub
valgrind ./Cub3D maps/map_bad_text_path1.cub
valgrind ./Cub3D maps/map_bad_text_path2.cub
valgrind ./Cub3D maps/map_bad_text_path3.cub
valgrind ./Cub3D maps/map_bad_text_path4.cub
