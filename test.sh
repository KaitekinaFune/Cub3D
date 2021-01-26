make re

echo ""
echo ""
echo  "Testing good maps:"
echo  "./Cub3D maps/map_valid_no_space.cub"
./Cub3D maps/map_valid_no_space.cub
echo "./Cub3D maps/map_valid_with_spaces.cub"
./Cub3D maps/map_valid_with_spaces.cub
echo "./Cub3D maps/map_valid_big.cub"
./Cub3D maps/map_valid_big.cub
echo ""
echo ""

echo "Testing bad maps:"
echo "Missing specifications:"
./Cub3D maps/map_bad_no_no.cub
./Cub3D maps/map_bad_no_so.cub
./Cub3D maps/map_bad_no_ea.cub
./Cub3D maps/map_bad_no_we.cub
./Cub3D maps/map_bad_no_s.cub
echo ""
echo ""
echo "Bad colors:"
./Cub3D maps/map_bad_f_color.cub
./Cub3D maps/map_bad_c_color.cub
echo ""
echo ""
echo "Missing line"
./Cub3D maps/map_bad_empty_spec.cub
echo ""
echo ""
echo "Double lines"
./Cub3D maps/map_bad_double.cub
echo ""
echo ""
echo "Empty line"
./Cub3D maps/map_bad_empty.cub
echo ""
echo ""
echo "Empty line in map"
./Cub3D maps/map_bad_hole.cub
echo ""
echo ""
echo "Missing textures:"
./Cub3D maps/map_bad_text_path0.cub
./Cub3D maps/map_bad_text_path1.cub
./Cub3D maps/map_bad_text_path2.cub
./Cub3D maps/map_bad_text_path3.cub
./Cub3D maps/map_bad_text_path4.cub
