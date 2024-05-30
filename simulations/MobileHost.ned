package retea_oportunista.simulations;

simple MobileHost
{
    parameters:
        int nodeId;
        int groupId;
        int totalNodes;
        int initialValue;
        @display("i=device/pc");
    gates:
        input in[];
        output out[];
}
