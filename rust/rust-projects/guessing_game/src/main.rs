use std::io;
use rand::Rng;
use std::cmp::Ordering;
fn main() {
    println!("請猜測一個數字！");

    println!("請輸入你的猜測數字。");

    // 隨機數字
    // 會位於目前執行緒（thread）並由作業系統提供種子（seed）。然後我們對隨機數字產生器呼叫 gen_range 方法。
    // 取 1 到 100 之間的數字。
    let secret = rand::thread_rng().gen_range(1..=100);
    println!("祕密數字為：{secret}");
    // let apple = 5; // 不可變的
    // let mut banana = 5; // 可變的

    loop {
        let mut guess = String::new();

        let read_line = io::stdin().read_line(&mut guess);
        read_line.expect("讀取失敗");
        // let guess : u32 = guess.trim().parse().expect("請輸入");
        let guess : u32 = match guess.trim().parse(){
            Ok(num)=>num,
            Err(_) => continue,
        };
        println!("你的猜測數字：{guess}");
    
        match guess.cmp(&secret) {
            Ordering::Less => println!("too small"),
            Ordering::Greater => print!("too big"),
            Ordering::Equal => {
                print!("win");
                break;
            },
        }
    }
    


    // println! 佔位符印出
    let x = 5;
    let y = 10;
    //透過 println! 佔位符印出數值
    println!("x = {x} and y+x = {}",y+2);
}
