using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Wwise_Occlusion : MonoBehaviour
{
    [SerializeField] private GameObject audioListener;
    private string RTPC_LoPass = "RTPC_Occlusion_LoPass";
    private string RTPC_Volume = "RTPC_Occlusion_Volume";
    private string nameOfListener;

    // Start is called before the first frame update
    void Start()
    {
        nameOfListener = audioListener.name;
        AkSoundEngine.RegisterGameObj(gameObject);
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 dir = audioListener.transform.position - gameObject.transform.position;
        RaycastHit hitInfo;
        bool hit = Physics.Raycast(gameObject.transform.position, dir, out hitInfo);

        if (hit) {
            if (hitInfo.collider.gameObject.name != nameOfListener)
            {
                Debug.Log("Doing occlusion");
                AkSoundEngine.SetRTPCValue(RTPC_LoPass, 50, gameObject);
                //AkSoundEngine.SetRTPCValue(RTPC_Volume, 1, sound_emitter);
            }
            else {
                AkSoundEngine.SetRTPCValue(RTPC_LoPass, 0, gameObject);
                //AkSoundEngine.SetRTPCValue(RTPC_Volume, 0, sound_emitter);
            }
        }
    }
}
