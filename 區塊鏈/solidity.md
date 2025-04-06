1. 編譯後分 EVM code or AIB(抽象語法)

2. deploy環境 
   2.1 javascript VM
       -> 注入Web3和-Web3提供商我们部署合同或发送交易到这些环境之一｡
        在JavaScript虚拟机中, 所有交易都将在浏览器的沙箱区块链中执行｡ JS虚拟机是它自己的内存中的区块链,
        每次重新加载时, 它都会启动一个新的区块链, 旧的区块链不会被保存｡
        这不是持久性的, 但它是在使用主网或测试网之前进行测试的理想选择｡
   2.2 injected Web3
        Remix将连接到一个注入的web3提供者, 比如Metamask,
        它又将连接到主网或测试网上的以太坊节点｡
        当你想在以太坊主网络或测试网络（例如Rinkeby）上部署合约或运行事务时, 这是很有用的｡
   2.3 Web3 Provider 
        Remix将使用URL和以太坊客户端（例如geth）连接到远程节点,这也是必需的｡

3. 3種註解 
     3.1 /// and // and /***/

4. EVM save data 方式
     4.1 storage
         - holds state variables
         - persistent and expensive(貴 cost gas)
         - like HDD
     4.2 stack 
     free
          ```
          // 声明这个函数是纯函数, 因为它不涉及区块链｡
          // 它既不修改区块链, 也不读取区块｡
          // 用的也是局部變量
          function f1() public pure returns(int){
               int x =5;
               x=x*2;
               return x;
          }
          ```
     4.3 memory
          - free
          - like ram
           ```
          // 声明这个函数是纯函数, 因为它不涉及区块链｡
          // 它既不修改区块链, 也不读取区块｡
          // 用的也是局部變量
          function f1() public pure returns(int){
               int memory x =5;
               x=x*2;
               return x;
          }
          ```
5. setter 會消耗 gas
6. deploy 時可以給預設值
7. 數值溢出問題(ex: uint8 > 255 會溢出) 在 0.8.0 會檢查，之前版本需要用 safeMath lib
     除非用 unchecked

8. array 分為 固定和動態
```
contract FixedSizeArrays{
     uint[3] public numbers = [1,2,3];


}
```
9. 全局變量
```
1.msg 重要全局變量
msg.sender
msg.value
msg.gas
msg.data
2. address(this) => current contract
3. block
block.timestamp alias for now
block.number
block.difficulty
block.gaslimit
tx.gasprice:gas price of the transaction

```

leftGas() => 當前交易還可以消耗的gas