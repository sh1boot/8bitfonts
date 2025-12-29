#include <unistd.h>

#include <cassert>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <array>
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <span>
#include <vector>

/*
░░─░━░│░┃░┄░┅░┆░┇░┈░┉░┊░┋░┌░┍░┎░┏░┐░┑░┒░┓░└░┕░┖░┗░┘░┙░┚░┛░├░┝░┞░┟░
░┠░┡░┢░┣░┤░┥░┦░┧░┨░┩░┪░┫░┬░┭░┮░┯░┰░┱░┲░┳░┴░┵░┶░┷░┸░┹░┺░┻░┼░┽░┾░┿░░
░░╀░╁░╂░╃░╄░╅░╆░╇░╈░╉░╊░╋░╌░╍░╎░╏░═░║░╒░╓░╔░╕░╖░╗░╘░╙░╚░╛░╜░╝░╞░╟░
░╠░╡░╢░╣░╤░╥░╦░╧░╨░╩░╪░╫░╬░╭░╮░╯░╰░╱░╲░╳░╴░╵░╶░╷░╸░╹░╺░╻░╼░╽░╾░╿░░
░░▀░▁░▂░▃░▄░▅░▆░▇░█░▉░▊░▋░▌░▍░▎░▏░▐░░░▒░▓░▔░▕░▖░▗░▘░▙░▚░▛░▜░▝░▞░▟░
░■░□░▢░▣░▤░▥░▦░▧░▨░▩░▪░▫░▬░▭░▮░▯░▰░▱░▲░△░▴░▵░▶░▷░▸░▹░►░▻░▼░▽░▾░▿░░
░░◀░◁░◂░◃░◄░◅░◆░◇░◈░◉░◊░○░◌░◍░◎░●░◐░◑░◒░◓░◔░◕░◖░◗░◘░◙░◚░◛░◜░◝░◞░◟░
░◠░◡░◢░◣░◤░◥░◦░◧░◨░◩░◪░◫░◬░◭░◮░◯░◰░◱░◲░◳░◴░◵░◶░◷░◸░◹░◺░◻░◼░◽░◾░◿░
░░🬀░🬁░🬂░🬃░🬄░🬅░🬆░🬇░🬈░🬉░🬊░🬋░🬌░🬍░🬎░🬏░🬐░🬑░🬒░🬓░🬔░🬕░🬖░🬗░🬘░🬙░🬚░🬛░🬜░🬝░🬞░🬟░
░🬠░🬡░🬢░🬣░🬤░🬥░🬦░🬧░🬨░🬩░🬪░🬫░🬬░🬭░🬮░🬯░🬰░🬱░🬲░🬳░🬴░🬵░🬶░🬷░🬸░🬹░🬺░🬻░🬼░🬽░🬾░🬿░░
░░🭀░🭁░🭂░🭃░🭄░🭅░🭆░🭇░🭈░🭉░🭊░🭋░🭌░🭍░🭎░🭏░🭐░🭑░🭒░🭓░🭔░🭕░🭖░🭗░🭘░🭙░🭚░🭛░🭜░🭝░🭞░🭟░
░🭠░🭡░🭢░🭣░🭤░🭥░🭦░🭧░🭨░🭩░🭪░🭫░🭬░🭭░🭮░🭯░🭰░🭱░🭲░🭳░🭴░🭵░🭶░🭷░🭸░🭹░🭺░🭻░🭼░🭽░🭾░🭿░░
░░🮀░🮁░🮂░🮃░🮄░🮅░🮆░🮇░🮈░🮉░🮊░🮋░🮌░🮍░🮎░🮏░🮐░🮑░🮒░🮔░🮕░🮖░🮗░🮘░🮙░🮚░🮛░🮜░🮝░🮞░🮟░░░
░🮠░🮡░🮢░🮣░🮤░🮥░🮦░🮧░🮨░🮩░🮪░🮫░🮬░🮭░🮮░🮯░🮰░🮱░🮲░🮳░🮴░🮵░🮶░🮷░🮸░🮹░🮺░🮻░🮼░🮽░🮾░🮿░░
░░🯀░🯁░🯂░🯃░🯄░🯅░🯆░🯇░🯈░🯉░🯊░🯋░🯌░🯍░🯎░🯏░🯐░🯑░🯒░🯓░🯔░🯕░🯖░🯗░🯘░🯙░🯚░🯛░🯜░🯝░🯞░🯟░
░🯠░🯡░🯢░🯣░🯤░🯥░🯦░🯧░🯨░🯩░🯪░🯫░🯬░🯭░🯮░🯯░🯰░🯱░🯲░🯳░🯴░🯵░🯶░🯷░🯸░🯹░🯺░░░░░░░░░░░░
░░𜰀░𜰁░𜰂░𜰃░𜰄░𜰅░𜰆░𜰇░𜰈░𜰉░𜰊░𜰋░𜰌░𜰍░𜰎░𜰏░𜰐░𜰑░𜰒░𜰓░𜰔░𜰕░𜰖░𜰗░𜰘░𜰙░𜰚░𜰛░𜰜░𜰝░𜰞░𜰟░
░𜰠░𜰡░𜰢░𜰣░𜰤░𜰥░𜰦░𜰧░𜰨░𜰩░𜰪░𜰫░𜰬░𜰭░𜰮░𜰯░𜰰░𜰱░𜰲░𜰳░𜰴░𜰵░𜰶░𜰷░𜰸░𜰹░𜰺░𜰻░𜰼░𜰽░𜰾░𜰿░░
░░𜱀░𜱁░𜱂░𜱃░𜱄░𜱅░𜱆░𜱇░𜱈░𜱉░𜱊░𜱋░𜱌░𜱍░𜱎░𜱏░𜱐░𜱑░𜱒░𜱓░𜱔░𜱕░𜱖░𜱗░𜱘░𜱙░𜱚░𜱛░𜱜░𜱝░𜱞░𜱟░
░𜱠░𜱡░𜱢░𜱣░𜱤░𜱥░𜱦░𜱧░𜱨░𜱩░𜱪░𜱫░𜱬░𜱭░𜱮░𜱯░𜱰░𜱱░𜱲░𜱳░𜱴░𜱵░𜱶░𜱷░𜱸░𜱹░𜱺░𜱻░𜱼░𜱽░𜱾░𜱿░░
░░𜲀░𜲁░𜲂░𜲃░𜲄░𜲅░𜲆░𜲇░𜲈░𜲉░𜲊░𜲋░𜲌░𜲍░𜲎░𜲏░𜲐░𜲑░𜲒░𜲓░𜲔░𜲕░𜲖░𜲗░𜲘░𜲙░𜲚░𜲛░𜲜░𜲝░𜲞░𜲟░
░𜲠░𜲡░𜲢░𜲣░𜲤░𜲥░𜲦░𜲧░𜲨░𜲩░𜲪░𜲫░𜲬░𜲭░𜲮░𜲯░𜲰░𜲱░𜲲░𜲳░𜲴░𜲵░𜲶░𜲷░𜲸░𜲹░𜲺░𜲻░𜲼░𜲽░𜲾░𜲿░░
░░𜳀░𜳁░𜳂░𜳃░𜳄░𜳅░𜳆░𜳇░𜳈░𜳉░𜳊░𜳋░𜳌░𜳍░𜳎░𜳏░𜳐░𜳑░𜳒░𜳓░𜳔░𜳕░𜳖░𜳗░𜳘░𜳙░𜳚░𜳛░𜳜░𜳝░𜳞░𜳟░
░𜳠░𜳡░𜳢░𜳣░𜳤░𜳥░𜳦░𜳧░𜳨░𜳩░𜳪░𜳫░𜳬░𜳭░𜳮░𜳯░𜳰░𜳱░𜳲░𜳳░𜳴░𜳵░𜳶░𜳷░𜳸░𜳹░𜳺░𜳻░𜳼░░░░░░░░
░░𜴀░𜴁░𜴂░𜴃░𜴄░𜴅░𜴆░𜴇░𜴈░𜴉░𜴊░𜴋░𜴌░𜴍░𜴎░𜴏░𜴐░𜴑░𜴒░𜴓░𜴔░𜴕░𜴖░𜴗░𜴘░𜴙░𜴚░𜴛░𜴜░𜴝░𜴞░𜴟░
░𜴠░𜴡░𜴢░𜴣░𜴤░𜴥░𜴦░𜴧░𜴨░𜴩░𜴪░𜴫░𜴬░𜴭░𜴮░𜴯░𜴰░𜴱░𜴲░𜴳░𜴴░𜴵░𜴶░𜴷░𜴸░𜴹░𜴺░𜴻░𜴼░𜴽░𜴾░𜴿░░
░░𜵀░𜵁░𜵂░𜵃░𜵄░𜵅░𜵆░𜵇░𜵈░𜵉░𜵊░𜵋░𜵌░𜵍░𜵎░𜵏░𜵐░𜵑░𜵒░𜵓░𜵔░𜵕░𜵖░𜵗░𜵘░𜵙░𜵚░𜵛░𜵜░𜵝░𜵞░𜵟░
░𜵠░𜵡░𜵢░𜵣░𜵤░𜵥░𜵦░𜵧░𜵨░𜵩░𜵪░𜵫░𜵬░𜵭░𜵮░𜵯░𜵰░𜵱░𜵲░𜵳░𜵴░𜵵░𜵶░𜵷░𜵸░𜵹░𜵺░𜵻░𜵼░𜵽░𜵾░𜵿░░
░░𜶀░𜶁░𜶂░𜶃░𜶄░𜶅░𜶆░𜶇░𜶈░𜶉░𜶊░𜶋░𜶌░𜶍░𜶎░𜶏░𜶐░𜶑░𜶒░𜶓░𜶔░𜶕░𜶖░𜶗░𜶘░𜶙░𜶚░𜶛░𜶜░𜶝░𜶞░𜶟░
░𜶠░𜶡░𜶢░𜶣░𜶤░𜶥░𜶦░𜶧░𜶨░𜶩░𜶪░𜶫░𜶬░𜶭░𜶮░𜶯░𜶰░𜶱░𜶲░𜶳░𜶴░𜶵░𜶶░𜶷░𜶸░𜶹░𜶺░𜶻░𜶼░𜶽░𜶾░𜶿░░
░░𜷀░𜷁░𜷂░𜷃░𜷄░𜷅░𜷆░𜷇░𜷈░𜷉░𜷊░𜷋░𜷌░𜷍░𜷎░𜷏░𜷐░𜷑░𜷒░𜷓░𜷔░𜷕░𜷖░𜷗░𜷘░𜷙░𜷚░𜷛░𜷜░𜷝░𜷞░𜷟░
░𜷠░𜷡░𜷢░𜷣░𜷤░𜷥░𜷦░𜷧░𜷨░𜷩░𜷪░𜷫░𜷬░𜷭░𜷮░𜷯░𜷰░𜷱░𜷲░𜷳░𜷴░𜷵░𜷶░𜷷░𜷸░𜷹░𜷺░𜷻░𜷼░𜷽░𜷾░𜷿░░
░░𜸀░𜸁░𜸂░𜸃░𜸄░𜸅░𜸆░𜸇░𜸈░𜸉░𜸊░𜸋░𜸌░𜸍░𜸎░𜸏░𜸐░𜸑░𜸒░𜸓░𜸔░𜸕░𜸖░𜸗░𜸘░𜸙░𜸚░𜸛░𜸜░𜸝░𜸞░𜸟░
░𜸠░𜸡░𜸢░𜸣░𜸤░𜸥░𜸦░𜸧░𜸨░𜸩░𜸪░𜸫░𜸬░𜸭░𜸮░𜸯░𜸰░𜸱░𜸲░𜸳░𜸴░𜸵░𜸶░𜸷░𜸸░𜸹░𜸺░𜸻░𜸼░𜸽░𜸾░𜸿░░
░░𜹀░𜹁░𜹂░𜹃░𜹄░𜹅░𜹆░𜹇░𜹈░𜹉░𜹊░𜹋░𜹌░𜹍░𜹎░𜹏░𜹐░𜹑░𜹒░𜹓░𜹔░𜹕░𜹖░𜹗░𜹘░𜹙░𜹚░𜹛░𜹜░𜹝░𜹞░𜹟░
░𜹠░𜹡░𜹢░𜹣░𜹤░𜹥░𜹦░𜹧░𜹨░𜹩░𜹪░𜹫░𜹬░𜹭░𜹮░𜹯░𜹰░𜹱░𜹲░𜹳░𜹴░𜹵░𜹶░𜹷░𜹸░𜹹░𜹺░𜹻░𜹼░𜹽░𜹾░𜹿░░
░░𜺀░𜺁░𜺂░𜺃░𜺄░𜺅░𜺆░𜺇░𜺈░𜺉░𜺊░𜺋░𜺌░𜺍░𜺎░𜺏░𜺐░𜺑░𜺒░𜺓░𜺔░𜺕░𜺖░𜺗░𜺘░𜺙░𜺚░𜺛░𜺜░𜺝░𜺞░𜺟░
░𜺠░𜺡░𜺢░𜺣░𜺤░𜺥░𜺦░𜺧░𜺨░𜺩░𜺪░𜺫░𜺬░𜺭░𜺮░𜺯░𜺰░𜺱░𜺲░𜺳░𜺺░𜺻░𜺼░𜺽░𜺾░𜺿░

 ▓█ ░▝🯤▘🯦▖🯥▗🯧🯦░𜰰𜰱𜰲𜰳 ░🯢░🯮🯭░🯪░🯩🯫░░░░
▕▓▉▕ ░ ░ ░🯤░ ░ 𜰴𜰵𜰶𜰷 ░𜸁░🯬🯯░🯨░🯡𜸀🯣░░░
🮇▓▊🭵 █▇▆▅▄▃▂▁  𜰸𜰹𜰺𜰻 ░🯠░◝◠◜░◞◡◟░
🮈▓▋🭴 ▓▓▓▓▓▓▓▓▓ 𜰼𜰽𜰾𜰿 ░
▐▓▌🭳  ▔🮂🮃▀🮄🮅🮆█      ░
🮉▓▍🭲🮵▔🭶🭷🭸🭹🭺🭻▁🮶🮀               🭽▔🭾
🮊▓▎🭱 𜲦𜲧 𜲨𜲩 𜲦𜲧 𜲨𜲩 𜲲𜲳 𜲶𜲷 𜳒𜳓 𜱚𜱛𜱜 ▏░▕
🮋▓▏🭰 𜲪𜲫 𜲬𜲭 𜲮𜲯 𜲰𜲱 𜲴𜲵 𜲸𜲹 𜳔𜳕 𜱝𜱞𜱟 🭼▁🭿
█▓ ▏𜰒─𜰋𜰌𜰌𜰍─𜰉𜰉𜰉𜰉─𜰐
12 123 1234 .1234. 123456 12345678  123456789abc
🭋🭀░ 🭯 ░ ◢◣ ░ 🭇🭃🭎🬼   🭇🭄🭏🬼    🭈🭄🭍🬿       🭈🭆🭂🭍🭑🬽
🭅🭐░🭮▓🭬░◢▓▓◣░🭇🭃▓▓🭎🬼 🭊🭁▓▓🭌🬿 🭊🭂▓▓▓▓🭏🬽  🭈🭆🭂▓▓▓▓▓▓🭍🭑🬽
🭖🭡░ 🭭 ░◥▓▓◤░🭢🭔▓▓🭟🭗 🭥🭒▓▓🭝🭚 🭣🭕▓▓▓▓🭞🭚  🭣🭧🭓▓▓▓▓▓▓🭞🭜🭘
🭦🭛░   ░ ◥◤ ░ 🭢🭔🭟🭗   🭢🭕🭠🭗    🭥🭓🭠🭘       🭣🭧🭓🭞🭜🭘
              🭢🭗
🯕🮮🮮🯗🯔🮮🯖░🯖🯔 ░🯞░░🮣🮧🮢░🯚░🮣🮢░ ░🯐🯑🯒🯓░🯐🯑🯒🯓░░🮭🮢🮣🮬░░🮣𜸉🮢░🮣𜸉🮢
░🯔🯖░🯕 🯗░🯗🯕░🯖 🯔 🮤🮮🮥🯙🮮🯛🮤🮥 🮮░🯒🯓🯐🯑🯝    🯟🮣🮩🮠🮡🮨🮢░🯙🮮🯛░🮤🮮🮥
 🯕🯗 ░🯜░🯖🮮🮮🯔🯗🮮🯕 🮡🮦🮠░🯘░🮡🮠░ ░░░░░░🯒🯓🯐🯑░🮡🮪░░🮫🮠░🮡𜸊🮠░🮡𜸊🮠
                           🭯
🮞🮏🮟 🮞🮑🮟 🮑🮑🮑🮑 🭯░🭯░🭯🭯░   🭮🭩🭬░🭨🭬░ 🭯 🭯🯪
🮍🮐🮌 ?🮐🮔 ░▒▓█ 🭨🮛🭪░🭨🭪░🭮🭩🭬░🮚░🭮🭪░░🭮🭫🭩🭫🭪
🮝🮎🮜 🮝🮒🮜 🮎🮎🮎🮎 🭭░🭭░🭭🭭░🭮🭫🭬🭮🭫🭬🯩🭫🯫░  🭭 🯨
┌─┬┐┏━┳┓ ┍━┯┑┎─┰┒       ╷ 
│ ││┃ ┃┃ │ ││┃ ┃┃ ╷ ╿ ╻╶┼╴
├─┼┤┣━╋┫ ┝━┿┥┠─╂┨╺┿╾┼╼╋╸╵ 
└─┴┘┗━┻┛ ┕━┷┙┖─┸┚ ╵░╽ ╹   
╭┈┬╮┏┉┳┓┌─┬┐╔═╦╗ ╒═╤╕╓─╥╖  𜸛𜸟𜸠𜸧 𜸚𜸟𜸵𜸤        𜹉𜹊𜹋𜹎𜹏
┊ ┆╎┋ ┇╏│ ││║ ║║ │ ││║ ║║  𜸩 𜸩𜸩 𜹋𜹍𜹌𜹈𜸫 𜸢 𜸬𜸴𜸻  𜸝𜸡𜸦 𜸣𜸜𜹈𜹇
├┄┼┤┣┅╋┫├─┼┤╠═╬╣ ╞═╪╡╟─╫╢  𜸨𜸟𜸺𜸶 𜸮𜸟𜸺𜸷  𜸪𜸲𜸸𜸯𜸸𜸳𜸱𜹁𜸰𜸹 𜸞𜸺𜸥 
╰╌┴╯┗╍┻┛└─┴┘╚═╩╝ ╘═╧╛╙─╨╜  𜸽𜸟𜹀𜹄 𜸾𜸟𜹃𜹅𜸬𜸴𜸻 𜸫 𜸢𜸿𜹂𜹆   𜸭𜸼𜹌𜹐
┌┬┐ ┌┲┓ ┌┲┓ ┏┳┓ ┏┱┐ ┏┱┐ ┌┬┐ ┌┬┐
├╆┪ ├╊┫ ├╄┩ ┡╇┩ ┡╃┤ ┣╉┤ ┢╅┤ ┢╈┪
└┺┛ └┺┛ └┴┘ └┴┘ └┴┘ ┗┹┘ ┗┹┘ ┗┻┛
┏┳┓ ┏┭┐ ┏┭┐ ┌┬┐ ┌┮┓ ┌┮┓ ┏┳┓ ┏┳┓
┣╃┦ ┣┽┤ ┣╅┧ ┟╁┧ ┟╆┫ ├┾┫ ┞╄┫ ┞╀┦
┗┵┘ ┗┵┘ ┗┻┛ ┗┻┛ ┗┻┛ └┶┛ └┶┛ └┴┘
*/

struct WeeString {
    static constexpr int kMaxLen = 7;
    constexpr WeeString() : data_{}, len_{0} {}
    constexpr WeeString(wchar_t c) : data_{} {
        if (c < 0x80) {
            data_[0] = c;
            data_[1] = '\0';
            len_ = 1;
        } else if (c < 0x800) {
            data_[0] = 0xc0 | (c >> 6);
            data_[1] = 0x80 | ((c >> 0) & 0x3f);
            data_[2] = '\0';
            len_ = 2;
        } else if (c < 0x10000) {
            data_[0] = 0xe0 | (c >> 12);
            data_[1] = 0x80 | ((c >> 6) & 0x3f);
            data_[2] = 0x80 | ((c >> 0) & 0x3f);
            data_[3] = '\0';
            len_ = 3;
        } else {
            data_[0] = 0xf0 | (c >> 18);
            data_[1] = 0x80 | ((c >> 12) & 0x3f);
            data_[2] = 0x80 | ((c >> 6) & 0x3f);
            data_[3] = 0x80 | ((c >> 0) & 0x3f);
            data_[4] = '\0';
            len_ = 4;
        }
    }

    operator char const*() const {
        return data_;
    }
    operator std::string_view() const {
        std::string_view r{data_, len_};
        std::cerr << r << std::endl;
        return r;
    }

  private:
    char data_[kMaxLen];
    uint8_t len_;
};

struct Glyph {
    static constexpr int kMaxWidth = 8;
    static constexpr int kMaxHeight = 16;

    Glyph(int height = 8, int width = 8, bool hflip = true, int shift = 0)
            : width_(width), height_(height), hflip_(hflip), shift_(shift) {
        assert(width <= kMaxWidth);
        assert(height <= kMaxHeight);
    }
    long read(FILE* file) {
        long position = ftell(file);
        if (fread(blob_, height_, 1, file) != 1) return -1;
        if (hflip_) hflip();
        return position;
    }
    template <size_t W, size_t H>
    uint64_t get_bitmap(int line, int col) const {
        constexpr uint64_t mask = ~(~uint64_t(1) << (W - 1));
        uint64_t bitmap = 0;
        for (int i = 0, s = 0; i < H; ++i, s += W) {
            int j = i + line;
            if (0 <= j && j < height_) {
                uint64_t b = uint64_t(blob_[j]) << 8 >> (col + 8);
                bitmap |= (b & mask) << s;
            }
        }
        return bitmap;
    }
    void hflip() {
        for (int i = 0; i < height_; ++i) {
            int x = blob_[i];
            x = ((x >> 1) & 0x55) | ((x & 0x55) << 1);
            x = ((x >> 2) & 0x33) | ((x & 0x33) << 2);
            x = ((x >> 4) & 0x0f) | ((x & 0x0f) << 4);
            blob_[i] = x >> shift_;
        }
    }

    const int width_;
    const int height_;
    const bool hflip_;
    const int shift_;
    uint8_t blob_[kMaxHeight];
};

template <size_t W, size_t H>
struct Patcher {
    constexpr Patcher(char const* s, wchar_t code) : code_(code) {
        mask_ = 0;
        test_ = 0;
        uint64_t b = 1;
        while (*s) {
            mask_ |= (*s == ' ' || *s == '@') ? b : 0;
            test_ |= (*s == '@') ? b : 0;
            b <<= 1;
            s++;
        }
    }

    uint64_t mask_, test_;
    WeeString code_;
};

template <size_t W, size_t H>
struct Decoder {
    static constexpr size_t PW = W + 2;
    static constexpr size_t PH = H + 2;
    using PatchType = Patcher<PW, PH>;
    static constexpr std::span<const PatchType> kNoPatches{};
    constexpr Decoder(wchar_t const* ptr,
                      std::span<const PatchType> patches = kNoPatches,
                      int advx = W, int advy = H)
            : advx_(advx), advy_(advy), patches_(patches) {
        for (WeeString& g : glyphs_) {
            assert(*ptr != '\0');
            g = *ptr++;
        }
        assert(*ptr == '\0');
    }
    constexpr Decoder(wchar_t const* ptr,
                      int advx, int advy = H)
            : Decoder(ptr, kNoPatches, advx, advy) {}

    bool decode(std::string& out, auto const& glyph, int row = 0) const {
        for (int col = 0; col < glyph.width_; col += advx_) {
            uint64_t bitmap = glyph.template get_bitmap<PW, PH>(row * advy_ - 1, col - 1);
            bool match = false;
            for (auto p : patches_) {
                if ((bitmap & p.mask_) == p.test_) {
                    out += p.code_;
                    match = true;
                    break;
                }
            }
            if (match) continue;
            int j = glyph.template get_bitmap<W, H>(row * advy_, col);
            assert(0 <= j && j < kMapSize);
            out += glyphs_[j];
        }
        return (row + 1) * advy_ < glyph.height_;
    }
    int get_rows(Glyph const& glyph) const { return (glyph.height_ - 1) / advy_ + 1; }

  private:
    static constexpr size_t kMapSize = size_t(1) << (W * H);
    WeeString glyphs_[kMapSize];
    const int advx_ = W, advy_ = H;
    std::span<const PatchType> patches_{};
};

struct CharSetBase {
    virtual void insert(wchar_t code, Glyph const& glyph, bool replace = true) = 0;
    virtual bool decode(std::string& out, Glyph const& glyph, int row) const = 0;
    CharSetBase(std::string_view name) : name_(name) {}
    size_t count(wchar_t code) {
        return chars_.count(code);
    }
    virtual int get_rows(Glyph const& glyph) const = 0;

    std::string_view get(wchar_t code) {
        if (count(code) == 0) return chars_[' '];
        return chars_[code];
    }
    auto begin() { return chars_.begin(); }
    auto end() { return chars_.end(); }

    std::string const name_;
    std::map<wchar_t, std::string> chars_;
};

template <int W, int H>
struct CharSet : public CharSetBase {
    CharSet(std::string_view name, Decoder<W, H> const& decoder)
        : CharSetBase(name), decoder_(decoder) { }

    void insert(wchar_t code, Glyph const& glyph, bool replace) override {
        if (replace == false && chars_.count(code)) return;
        std::string image;
        for (int row = 0; decoder_.decode(image, glyph, row); ++row) {
            image += "#\n";
        }
        image += "##\n";
        chars_[code] = image;
    }
    bool decode(std::string& out, Glyph const& glyph, int row) const override {
        return decoder_.decode(out, glyph, row);
    }
    int get_rows(Glyph const& glyph) const override { return decoder_.get_rows(glyph); }

    Decoder<W, H> const& decoder_;
};


static constexpr wchar_t braille_data[] =
   L"⠀⠁⠈⠉⠂⠃⠊⠋⠐⠑⠘⠙⠒⠓⠚⠛"
    "⠄⠅⠌⠍⠆⠇⠎⠏⠔⠕⠜⠝⠖⠗⠞⠟"
    "⠠⠡⠨⠩⠢⠣⠪⠫⠰⠱⠸⠹⠲⠳⠺⠻"
    "⠤⠥⠬⠭⠦⠧⠮⠯⠴⠵⠼⠽⠶⠷⠾⠿"
    "⡀⡁⡈⡉⡂⡃⡊⡋⡐⡑⡘⡙⡒⡓⡚⡛"
    "⡄⡅⡌⡍⡆⡇⡎⡏⡔⡕⡜⡝⡖⡗⡞⡟"
    "⡠⡡⡨⡩⡢⡣⡪⡫⡰⡱⡸⡹⡲⡳⡺⡻"
    "⡤⡥⡬⡭⡦⡧⡮⡯⡴⡵⡼⡽⡶⡷⡾⡿"
    "⢀⢁⢈⢉⢂⢃⢊⢋⢐⢑⢘⢙⢒⢓⢚⢛"
    "⢄⢅⢌⢍⢆⢇⢎⢏⢔⢕⢜⢝⢖⢗⢞⢟"
    "⢠⢡⢨⢩⢢⢣⢪⢫⢰⢱⢸⢹⢲⢳⢺⢻"
    "⢤⢥⢬⢭⢦⢧⢮⢯⢴⢵⢼⢽⢶⢷⢾⢿"
    "⣀⣁⣈⣉⣂⣃⣊⣋⣐⣑⣘⣙⣒⣓⣚⣛"
    "⣄⣅⣌⣍⣆⣇⣎⣏⣔⣕⣜⣝⣖⣗⣞⣟"
    "⣠⣡⣨⣩⣢⣣⣪⣫⣰⣱⣸⣹⣲⣳⣺⣻"
    "⣤⣥⣬⣭⣦⣧⣮⣯⣴⣵⣼⣽⣶⣷⣾⣿";

static constexpr wchar_t braille6_data[] =
   L" 𜹑𜹒𜹓𜹔𜹕𜹖𜹗𜹘𜹙𜹚𜹛𜹜𜹝𜹞𜹟"
    "𜹠𜹡𜹢𜹣𜹤𜹥𜹦𜹧𜹨𜹩𜹪𜹫𜹬𜹭𜹮𜹯"
    "𜹰𜹱𜹲𜹳𜹴𜹵𜹶𜹷𜹸𜹹𜹺𜹻𜹼𜹽𜹾𜹿"
    "𜺀𜺁𜺂𜺃𜺄𜺅𜺆𜺇𜺈𜺉𜺊𜺋𜺌𜺍𜺎𜺏";

static constexpr wchar_t braille4_data[] =
   L" 𜰡𜰢𜰣𜰤𜰥𜰦𜰧𜰨𜰩𜰪𜰫𜰬𜰭𜰮𜰯";

static constexpr wchar_t block_data[] =
   L" 𜺨𜺫🮂𜴀▘𜴁𜴂𜴃𜴄▝𜴅𜴆𜴇𜴈▀"
    "𜴉𜴊𜴋𜴌🯦𜴍𜴎𜴏𜴐𜴑𜴒𜴓𜴔𜴕𜴖𜴗"
    "𜴘𜴙𜴚𜴛𜴜𜴝𜴞𜴟🯧𜴠𜴡𜴢𜴣𜴤𜴥𜴦"
    "𜴧𜴨𜴩𜴪𜴫𜴬𜴭𜴮𜴯𜴰𜴱𜴲𜴳𜴴𜴵🮅"
    "𜺣𜴶𜴷𜴸𜴹𜴺𜴻𜴼𜴽𜴾𜴿𜵀𜵁𜵂𜵃𜵄"
    "▖𜵅𜵆𜵇𜵈▌𜵉𜵊𜵋𜵌▞𜵍𜵎𜵏𜵐▛"
    "𜵑𜵒𜵓𜵔𜵕𜵖𜵗𜵘𜵙𜵚𜵛𜵜𜵝𜵞𜵟𜵠"
    "𜵡𜵢𜵣𜵤𜵥𜵦𜵧𜵨𜵩𜵪𜵫𜵬𜵭𜵮𜵯𜵰"
    "𜺠𜵱𜵲𜵳𜵴𜵵𜵶𜵷𜵸𜵹𜵺𜵻𜵼𜵽𜵾𜵿"
    "𜶀𜶁𜶂𜶃𜶄𜶅𜶆𜶇𜶈𜶉𜶊𜶋𜶌𜶍𜶎𜶏"
    "▗𜶐𜶑𜶒𜶓▚𜶔𜶕𜶖𜶗▐𜶘𜶙𜶚𜶛▜"
    "𜶜𜶝𜶞𜶟𜶠𜶡𜶢𜶣𜶤𜶥𜶦𜶧𜶨𜶩𜶪𜶫"
    "▂𜶬𜶭𜶮𜶯𜶰𜶱𜶲𜶳𜶴𜶵𜶶𜶷𜶸𜶹𜶺"
    "𜶻𜶼𜶽𜶾𜶿𜷀𜷁𜷂𜷃𜷄𜷅𜷆𜷇𜷈𜷉𜷊"
    "𜷋𜷌𜷍𜷎𜷏𜷐𜷑𜷒𜷓𜷔𜷕𜷖𜷗𜷘𜷙𜷚"
    "▄𜷛𜷜𜷝𜷞▙𜷟𜷠𜷡𜷢▟𜷣▆𜷤𜷥█";

static constexpr wchar_t block6_data[] =
   L" 🬀🬁🬂🬃🬄🬅🬆🬇🬈🬉🬊🬋🬌🬍🬎"
    "🬏🬐🬑🬒🬓▌🬔🬕🬖🬗🬘🬙🬚🬛🬜🬝"
    "🬞🬟🬠🬡🬢🬣🬤🬥🬦🬧▐🬨🬩🬪🬫🬬"
    "🬭🬮🬯🬰🬱🬲🬳🬴🬵🬶🬷🬸🬹🬺🬻█";

static constexpr wchar_t block4_data[] = L" ▘▝▀▖▌▞▛▗▚▐▜▄▙▟█";
static constexpr wchar_t edge4_data[] =  L" ┛┕━┒┃╆┏┌╃│┑─┖┘ ";

static constexpr wchar_t block2_data[] =
   L" ▀▄█";

static constexpr Patcher<3,4> block2_shadow_data[]{
    { "@.."
      "@ ."
      ". ."
      "...", L'🮐' },
    { "@.."
      "  ."
      ". ."
      "...", L'🮎' },
    { " .."
      "@ ."
      ". ."
      "...", L'🮏' },
    { "..."
      "@@."
      ". ."
      "...", L'🮑' },
    { "@.."
      ". ."
      ".@."
      "...", L'🮒' },
};
#if 0
    { "---"
      "-@ "
      "@ -"
      "---", L'🮜' },
    { "---"
      " @-"
      "- @"
      "-- ", L'🮝' },
    { "---"
      "@ -"
      "-@ "
      "---", L'🮟' },
    { "---"
      "- @"
      " @-"
      "---", L'🮞' },
#endif

const Decoder<2,4> braille(braille_data);
const Decoder<2,3> braille6(braille6_data);
const Decoder<2,2> braille4(braille4_data);
const Decoder<2,4> block(block_data);
const Decoder<2,3> block6(block6_data);
const Decoder<2,2> block4(block4_data);
const Decoder<2,2> outline4(edge4_data, 1, 1);
const Decoder<1,2> block2(block2_data);
const Decoder<1,2> block2shadow(block2_data, block2_shadow_data);

CharSet<2,4> dots2x4("2dot", braille);
CharSet<2,3> dots2x3("3dot", braille6);
CharSet<2,2> dots2x2("4dot", braille4);
CharSet<2,4> blocks2x4("2", block);
CharSet<2,3> blocks2x3("3", block6);
CharSet<2,2> blocks2x2("4", block4);
CharSet<1,2> blocks1x2("4wide", block2);
CharSet<1,2> blocks1x2shadow("4shadow", block2shadow);
CharSet<2,2> outline2x2("8outline", outline4);

CharSetBase* allsets[] = {
    &dots2x4,
    &dots2x3,
    &dots2x2,
    &blocks2x4,
    &blocks2x3,
    &blocks2x2,
    &blocks1x2,
    &blocks1x2shadow,
    &outline2x2,
};

int main(int argc, char** argv) {
    std::filesystem::path input = "c64.bin";
    std::filesystem::path output;
    std::filesystem::path mapfile;
    int seek = 0, shift = 0;
    int width = 8, height = 8;
    bool view = false, flip = true;

    int opt;
    while ((opt = getopt(argc, argv, "vW:H:S:Mk:m:i:o:")) != -1) {
        switch (opt) {
        case 'v':
            view = true;
            break;
        case 'W':
            width = atoi(optarg);
            break;
        case 'H':
            height = atoi(optarg);
            break;
        case 'S':
            shift = atoi(optarg);
            break;
        case 'M':
            flip = !flip;
            break;
        case 'k':
            seek = strtoul(optarg, nullptr, 0);
        case 'm':
            mapfile = optarg;
            break;
        case 'i':
            input = optarg;
            break;
        case 'o':
            output = optarg;
            break;
        default:
            std::cerr << "oops, bad command line argument." << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    if (mapfile.empty()) {
        mapfile = input;
        mapfile.replace_extension(".map");
    }
    if (output.empty()) output = input.stem();
    std::string base = output.filename();

    FILE* blob = fopen(input.c_str(), "rb");
    if (blob == nullptr) {
        perror(input.c_str());
        exit(EXIT_FAILURE);
    }
    if (seek) fseek(blob, seek, SEEK_SET);
    FILE* map = fopen(mapfile.c_str(), "rt");

    Glyph glyph(height, width, flip, shift);
    wchar_t code = 32;
    long position;
    while ((position = glyph.read(blob)) >= 0) {
        if (map != nullptr) {
            char metadata[1024];
            fgets(metadata, sizeof(metadata), map);
            if (metadata[0] == 'U' && metadata[1] == '+') {
                code = strtoull(metadata + 2, nullptr, 16);
            } else {
                code = 0;
            }
        }
        if (code > 0 && !view) {
            for (auto set : allsets) {
                set->insert(code, glyph);
            }
        } else {
            std::string dump;
            bool more = true;
            for (int row = 0; more == true; ++row) {
                more = false;
                for (auto set : allsets) {
                    more |= set->decode(dump, glyph, row);
                    dump += "  ";
                }
                dump += '\n';
            }
            std::cout << "unused @0x" << std::hex << position << std::dec << ":\n" << dump;
        }
        code++;
    }
    if (!view) {
        std::string cmdline;
        for (int i = 0; i < argc; ++i) {
            cmdline += " ";
            cmdline += argv[i];
        }
        for (auto set : allsets) {
            auto filename = output;
            filename.replace_filename(std::string(output.filename()) + "-" + set->name_);
            filename.replace_extension(".tlf");
            FILE* font = fopen(filename.c_str(), "wt");
            if (font == nullptr) {
                perror(filename.c_str());
                continue;
            }
            fprintf(font, "tlf2a$ %d %d 40 -1 1 0 0 0\n"
                          "#%s (set: %s)\n",
                          set->get_rows(glyph), set->get_rows(glyph), cmdline.c_str(), set->name_.c_str());

            for (wchar_t code = 32; code < 127; ++code) {
                auto s = set->get(code);
                fwrite(s.data(), 1, s.size(), font);
            }
            for (wchar_t code : L"ÄÖÜäöüß") {
                if (code == L'\0') continue;
                auto s = set->get(code);
                fwrite(s.data(), 1, s.size(), font);
            }

            for (auto it : *set) {
                if (it.first < 127 || wcschr(L"ÄÖÜäöüß", it.first)) {
                    continue;
                }
                fprintf(font, "0x%06x\n%.*s", it.first, int(it.second.size()), it.second.data());
            }
            fclose(font);
        }
    }
    if (blob != nullptr) fclose(blob);
    if (map != nullptr) fclose(map);
    return 0;
}
