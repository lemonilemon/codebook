sy on
set ru nu cin cul sc so=3 ts=4 sw=4 bs=2 ls=2 mouse=a
inoremap {<CR> {<CR>}<C-o>O
map <F7> :w<CR>:!g++ "%" -std=c++17 -Wall -Wextra -Wshadow -Wconversion -fsanitize=address,undefined -g && ./a.out<CR>